/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Biquad.h"
#include <math.h>

//==============================================================================
MultiDistortionAudioProcessor::MultiDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), sliderState(*this, nullptr, "params", createParameterLayout())
#endif
{
}

MultiDistortionAudioProcessor::~MultiDistortionAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout MultiDistortionAudioProcessor::createParameterLayout(){
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back( std::make_unique<AudioParameterFloat> ("gainLow", "Gain Low", -24.f, 24.f, 0.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("gainMid", "Gain Mid", -24.f, 24.f, 0.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("gainHiMid", "Gain HiMid", -24.f, 24.f, 0.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("gainHigh", "Gain High", -24.f, 24.f, 0.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("lowMidCrossover","Low Mid Crossover",20.f, 349.f, 200.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("midCrossover","Mid Crossover",350.f, 4999.f, 1500.f) );
    params.push_back( std::make_unique<AudioParameterFloat> ("midHighCrossover","Mid High Crossover",5000.f, 20000.f, 8000.f) );
    params.push_back( std::make_unique<AudioParameterFloat>("mixPerc", "Wet/Dry", 0.f, 100.f, 100.f) );
    params.push_back( std::make_unique<AudioParameterFloat>("outputGain", "Output Gain", -24.f, 24.f, 0.f) );
    params.push_back( std::make_unique<AudioParameterBool>("lowBandisOff", "Bypass Low", false) );
    params.push_back( std::make_unique<AudioParameterBool>("midBandisOff", "Bypass Mid", false) );
    params.push_back( std::make_unique<AudioParameterBool>("hiMidBandisOff", "Bypass High Mid", false) );
    params.push_back( std::make_unique<AudioParameterBool>("highBandisOff", "Bypass High", false) );
//    params.push_back( std::make_unique<AudioParameterInt>("distortionTypeLow", "Distortion Type Low", 1, 5, 3) );
//    params.push_back( std::make_unique<AudioParameterInt>("distortionTypeMid", "Distortion Type Mid", 1, 5, 3) );
//    params.push_back( std::make_unique<AudioParameterInt>("distortionTypeHiMid", "Distortion Type Hi Mid", 1, 5, 3) );
//    params.push_back( std::make_unique<AudioParameterInt>("distortionTypeHigh", "Distortion Type High", 1, 5, 3) );
    
    
    return { params.begin() , params.end() };
    
}

//==============================================================================
const juce::String MultiDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultiDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultiDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultiDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultiDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultiDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultiDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultiDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MultiDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultiDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MultiDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    multiband.prepare(sampleRate);
    
}

void MultiDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultiDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MultiDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    float lowMidCrossoverFreq = *sliderState.getRawParameterValue("lowMidCrossover");
    float midCrossoverFreq = *sliderState.getRawParameterValue("midCrossover");
    float midHighCrossoverFreq = *sliderState.getRawParameterValue("midHighCrossover");
    
    float gainLow = *sliderState.getRawParameterValue("gainLow");
    float gainMid = *sliderState.getRawParameterValue("gainMid");
    float gainHiMid = *sliderState.getRawParameterValue("gainHiMid");
    float gainHigh = *sliderState.getRawParameterValue("gainHigh");
    
    bool lowBandisOff = *sliderState.getRawParameterValue("lowBandisOff");
    bool midBandisOff = *sliderState.getRawParameterValue("midBandisOff");
    bool hiMidBandisOff = *sliderState.getRawParameterValue("hiMidBandisOff");
    bool highBandisOff = *sliderState.getRawParameterValue("highBandisOff");
    
    float mixPerc = *sliderState.getRawParameterValue("mixPerc");
    
    float outputGain = *sliderState.getRawParameterValue("outputGain");
    
    multiband.setCutoffFreqLow(lowMidCrossoverFreq);
    multiband.setCutoffFreqLowMid(lowMidCrossoverFreq, midCrossoverFreq);
    multiband.setCutoffFreqHighMid(midCrossoverFreq, midHighCrossoverFreq);
    multiband.setCutoffFreqHigh(midHighCrossoverFreq);

    distortionLow.setGain(gainLow);
    distortionMid.setGain(gainMid);
    distortionHiMid.setGain(gainHiMid);
    distortionHigh.setGain(gainHigh);

    distortionLow.setThresh(thresh);
    distortionMid.setThresh(thresh);
    distortionHiMid.setThresh(thresh);
    distortionHigh.setThresh(thresh);

    distortionLow.setDistortionType(distortionTypeLow);
    distortionMid.setDistortionType(distortionTypeMid);
    distortionHiMid.setDistortionType(distortionTypeHiMid);
    distortionHigh.setDistortionType(distortionTypeHigh);


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // Separate signal into 4 bands based on filters in Multiband class.
        // Process each band individually based on distortionType and gain for each band
        for (int n = 0; n < buffer.getNumSamples(); ++n){
            
            float x = buffer.getWritePointer(channel)[n];
            float xLow = multiband.filterLow(x,channel);
            float xLowMid = multiband.filterLowMid(x,channel);
            float xHighMid = multiband.filterHighMid(x,channel);
            float xHigh = multiband.filterHigh(x,channel);
            
            // distortion.processSample
            if (lowBandisOff){
                xLow = xLow;
            }
            else
            {
                xLow = distortionLow.processSample(xLow, channel);
            }
            if (midBandisOff){
                xLowMid = xLowMid;
            }
            else
            {
                xLowMid = distortionMid.processSample(xLowMid, channel);
            }
            if (hiMidBandisOff){
                xHighMid = xHighMid;
            }
            else
            {
                xHighMid = distortionHiMid.processSample(xHighMid, channel);
            }
            if (highBandisOff){
                xHigh = xHigh;
            }
            else
            {
                xHigh = distortionHigh.processSample(xHigh, channel);
            }


            // Add processed bands back together for full signal
            float xDist = xLow + xLowMid + xHighMid + xHigh;
            // Mix Knob Adjustment
            float yMix = (xDist * (mixPerc/100.f)) + (x * (1-(mixPerc/100.f)));
            float y = yMix * (pow(10.f, outputGain/20.f));
            buffer.getWritePointer(channel)[n] = y;
            
        }
    }
}

//==============================================================================
bool MultiDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MultiDistortionAudioProcessor::createEditor()
{
    return new MultiDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void MultiDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto currentState =  sliderState.copyState();
    std::unique_ptr<XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);

}

void MultiDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xml ( getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName("params")){
        sliderState.replaceState(ValueTree::fromXml(*xml));
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiDistortionAudioProcessor();
}
