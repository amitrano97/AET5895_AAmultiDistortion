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
                       )
#endif
{
    addParameter(gainLow = new AudioParameterFloat("gainLowDistortion", // string for identifying parameter in code
                                                   "Gain Low", // string shown in DAW to user
                                                   -24.f, // minimum value for range
                                                   24.f, // maximum value for range
                                                   0.f // Default Value for range
                                                   ));
    
    
}

MultiDistortionAudioProcessor::~MultiDistortionAudioProcessor()
{
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
    
    multiband.setCutoffFreqLow(lowMidCrossoverFreq);
    multiband.setCutoffFreqLowMid(lowMidCrossoverFreq, midCrossoverFreq);
    multiband.setCutoffFreqHighMid(midCrossoverFreq, midHighCrossoverFreq);
    multiband.setCutoffFreqHigh(midHighCrossoverFreq);
    
    distortionLow.setGain(*gainLow);
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
    std::unique_ptr<XmlElement> xml (new XmlElement("MultiDistortionParameters") );
    xml->setAttribute("gainLowDistortion", (double) *gainLow);
    copyXmlToBinary(*xml, destData);
}

void MultiDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr){
        if (xml->hasTagName("MultiDistortionParameters")){
            *gainLow = xml->getDoubleAttribute("gainLowDistortion",5.f);
        }
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultiDistortionAudioProcessor();
}
