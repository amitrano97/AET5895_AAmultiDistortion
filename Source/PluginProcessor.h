/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Distortion.h"
#include "Multiband.h"

//==============================================================================
/**
*/
class MultiDistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MultiDistortionAudioProcessor();
    ~MultiDistortionAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float thresh = 0.7f;
    
    
    
    float gainLow = 1.f;
    float gainMid = 1.f;
    float gainHiMid = 1.f;
    float gainHigh = 1.f;
    
    bool lowBandisOff = false; // true means band is muted
    bool midBandisOff = false;
    bool hiMidBandisOff = false;
    bool highBandisOff = false;
    
    float lowMidCrossoverFreq = 250.f;
    float midCrossoverFreq = 2000.f;
    float midHighCrossoverFreq = 8000.f;
    
    float mixPerc = 100.f;
    
private:
    
    Distortion distortion;
    Multiband multiband;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiDistortionAudioProcessor)
};
