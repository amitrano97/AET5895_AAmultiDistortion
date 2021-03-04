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
                                             public juce::Slider::Listener,
                                             public juce::ComboBox::Listener,
                                             public juce::Button::Listener
{
public:
    MultiDistortionAudioProcessorEditor (MultiDistortionAudioProcessor&);
    ~MultiDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider * slider) override;
    void comboBoxChanged(ComboBox * comboBox) override;
    void buttonClicked(Button * button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiDistortionAudioProcessor& audioProcessor;
    
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiDistortionAudioProcessorEditor)
};
