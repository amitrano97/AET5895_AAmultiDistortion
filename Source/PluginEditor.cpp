/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultiDistortionAudioProcessorEditor::MultiDistortionAudioProcessorEditor (MultiDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    
    gainKnobLow.addListener(this);
    gainKnobLow.setBounds(100, 50, 125, 125);
    gainKnobLow.setValue(audioProcessor.gainLow);
    gainKnobLow.setRange(10.f, 1000.f,1.f);
    gainKnobLow.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    gainKnobLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobLow);
}

MultiDistortionAudioProcessorEditor::~MultiDistortionAudioProcessorEditor()
{
}

//==============================================================================
void MultiDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MultiDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
