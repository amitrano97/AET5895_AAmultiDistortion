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
                                             public juce::ComboBox::Listener

{
public:
    MultiDistortionAudioProcessorEditor (MultiDistortionAudioProcessor&);
    ~MultiDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //void sliderValueChanged(Slider * slider) override;
    //void comboBoxChanged(ComboBox * comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultiDistortionAudioProcessor& audioProcessor;
    
    Slider gainKnobLow;
    ComboBox distortionTypeLow;
    
    Slider gainKnobMid;
    ComboBox distortionTypeMid;
    
    Slider gainKnobHiMid;
    ComboBox distortionTypeHiMid;
    
    Slider gainKnobHigh;
    ComboBox distortionTypeHigh;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiDistortionAudioProcessorEditor)
};
