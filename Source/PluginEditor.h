/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"



//==============================================================================
/**
*/
class MultiDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                public juce::ComboBox::Listener

{
public:
    MultiDistortionAudioProcessorEditor (MultiDistortionAudioProcessor&);
    ~MultiDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
//    void sliderValueChanged(Slider * slider) override;
    void comboBoxChanged(ComboBox * comboBox) override;
//    void buttonClicked(Button * button) override;
//
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiDistortionAudioProcessor& audioProcessor;
    
    Label mixLabel;
    Label outputLabel;
    Label lowGainLabel;
    Label midGainLabel;
    Label hiMidGainLabel;
    Label highGainLabel;
    
    Slider gainKnobLow;
    ComboBox distortionTypeLow;
    ToggleButton lowBandOff;

    Slider lowMidCrossover;

    Slider gainKnobMid;
    ComboBox distortionTypeMid;
    ToggleButton midBandOff;

    Slider midCrossover;

    Slider gainKnobHiMid;
    ComboBox distortionTypeHiMid;
    ToggleButton hiMidBandOff;

    Slider midHighCrossover;

    Slider gainKnobHigh;
    ComboBox distortionTypeHigh;
    ToggleButton highBandOff;
    
    Slider mixKnob;
    
    Slider outputKnob;
    
public:

    std::vector<std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment>> buttonAttachments;
//    std::vector<std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>> comboBoxAttachments;
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiDistortionAudioProcessorEditor)
};
