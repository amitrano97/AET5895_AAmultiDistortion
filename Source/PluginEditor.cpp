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
    gainKnobLow.setBounds(100, 90, 100, 100);
    gainKnobLow.setValue(0);//audioProcessor.gainLow
    gainKnobLow.setRange(10.f, 1000.f,1.f);
    gainKnobLow.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobLow.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobLow);
    
    distortionTypeLow.addListener(this);
    distortionTypeLow.addItem("Full Wave", 1);
    distortionTypeLow.addItem("Half Wave", 2);
    distortionTypeLow.addItem("Hard Clip", 3);
    distortionTypeLow.addItem("Cubic", 4);
    distortionTypeLow.addItem("arctan", 5);
    distortionTypeLow.setSelectedId(4);
    distortionTypeLow.setBounds(100, 180, 120, 40);
    addAndMakeVisible(distortionTypeLow);
    
    gainKnobMid.addListener(this);
    gainKnobMid.setBounds(200, 90, 100, 100);
    gainKnobMid.setValue(0);//audioProcessor.gainMid
    gainKnobMid.setRange(10.f, 1000.f,1.f);
    gainKnobMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobMid);
    
    distortionTypeMid.addListener(this);
    distortionTypeMid.addItem("Full Wave", 1);
    distortionTypeMid.addItem("Half Wave", 2);
    distortionTypeMid.addItem("Hard Clip", 3);
    distortionTypeMid.addItem("Cubic", 4);
    distortionTypeMid.addItem("arctan", 5);
    distortionTypeMid.setSelectedId(4);
    distortionTypeMid.setBounds(200, 180, 120, 40);
    addAndMakeVisible(distortionTypeMid);
    
    gainKnobHiMid.addListener(this);
    gainKnobHiMid.setBounds(300, 90, 100, 100);
    gainKnobHiMid.setValue(0);//audioProcessor.gainHiMid
    gainKnobHiMid.setRange(10.f, 1000.f,1.f);
    gainKnobHiMid.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobHiMid.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobHiMid);
    
    distortionTypeHiMid.addListener(this);
    distortionTypeHiMid.addItem("Full Wave", 1);
    distortionTypeHiMid.addItem("Half Wave", 2);
    distortionTypeHiMid.addItem("Hard Clip", 3);
    distortionTypeHiMid.addItem("Cubic", 4);
    distortionTypeHiMid.addItem("arctan", 5);
    distortionTypeHiMid.setSelectedId(4);
    distortionTypeHiMid.setBounds(300, 180, 120, 40);
    addAndMakeVisible(distortionTypeHiMid);
    
    gainKnobHigh.addListener(this);
    gainKnobHigh.setBounds(400, 90, 100, 100);
    gainKnobHigh.setValue(0);//audioProcessor.gainHigh
    gainKnobHigh.setRange(10.f, 1000.f,1.f);
    gainKnobHigh.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 75, 25);
    gainKnobHigh.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobHigh);
    
    distortionTypeHigh.addListener(this);
    distortionTypeHigh.addItem("Full Wave", 1);
    distortionTypeHigh.addItem("Half Wave", 2);
    distortionTypeHigh.addItem("Hard Clip", 3);
    distortionTypeHigh.addItem("Cubic", 4);
    distortionTypeHigh.addItem("arctan", 5);
    distortionTypeHigh.setSelectedId(4);
    distortionTypeHigh.setBounds(400, 180, 120, 40);
    addAndMakeVisible(distortionTypeHigh);
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
