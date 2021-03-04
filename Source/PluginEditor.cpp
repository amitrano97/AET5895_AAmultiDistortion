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
    setSize (800, 300);
    
    gainKnobLow.addListener(this);
    gainKnobLow.setBounds(40, 60, 100, 90);
    gainKnobLow.setValue(audioProcessor.gainLow);
    gainKnobLow.setRange(0.f, 4.f, .1f);
    gainKnobLow.setSkewFactorFromMidPoint(1.f);
    gainKnobLow.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobLow);
    
    lowGainLabel.setText("Gain Low", juce::dontSendNotification);
    lowGainLabel.attachToComponent(&gainKnobLow, false);
    addAndMakeVisible(lowGainLabel);
    
    distortionTypeLow.addListener(this);
    distortionTypeLow.addItem("Full Wave", 1);
    distortionTypeLow.addItem("Half Wave", 2);
    distortionTypeLow.addItem("Hard Clip", 3);
    distortionTypeLow.addItem("Cubic", 4);
    distortionTypeLow.addItem("arctan", 5);
    distortionTypeLow.setSelectedId(1);
    distortionTypeLow.setBounds(40, 160, 100, 20);
    addAndMakeVisible(distortionTypeLow);
    
    lowBandOff.addListener(this);
    lowBandOff.setBounds(50, 200, 80, 15);
    lowBandOff.setToggleState(audioProcessor.lowBandOff, dontSendNotification);
    lowBandOff.setButtonText("Band Off");
    addAndMakeVisible(lowBandOff);
    
    lowMidCrossover.addListener(this);
    lowMidCrossover.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lowMidCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    lowMidCrossover.setTextValueSuffix(" Hz");
    lowMidCrossover.setValue(audioProcessor.lowMidCrossover);
    lowMidCrossover.setRange(20.f, 2000.f, 1.f);
    lowMidCrossover.setBounds(100, 220, 100, 60);
    addAndMakeVisible(lowMidCrossover);
    
    gainKnobMid.addListener(this);
    gainKnobMid.setBounds(180, 40, 100, 90);
    gainKnobMid.setValue(audioProcessor.gainMid);
    gainKnobMid.setRange(0.f, 4.f, .1f);
    gainKnobMid.setSkewFactorFromMidPoint(1.f);
    gainKnobMid.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobMid);
    
    midGainLabel.setText("Gain Mid", juce::dontSendNotification);
    midGainLabel.attachToComponent(&gainKnobMid, false);
    addAndMakeVisible(midGainLabel);
    
    distortionTypeMid.addListener(this);
    distortionTypeMid.addItem("Full Wave", 1);
    distortionTypeMid.addItem("Half Wave", 2);
    distortionTypeMid.addItem("Hard Clip", 3);
    distortionTypeMid.addItem("Cubic", 4);
    distortionTypeMid.addItem("arctan", 5);
    distortionTypeMid.setSelectedId(2);
    distortionTypeMid.setBounds(180, 140, 100, 20);
    addAndMakeVisible(distortionTypeMid);
    
    midBandOff.addListener(this);
    midBandOff.setBounds(190, 200, 80, 15);
    midBandOff.setToggleState(audioProcessor.midBandOff, dontSendNotification);
    midBandOff.setButtonText("Band Off");
    addAndMakeVisible(midBandOff);
    
    midCrossover.addListener(this);
    midCrossover.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    midCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    midCrossover.setTextValueSuffix(" Hz");
    midCrossover.setValue(audioProcessor.midCrossover);
    midCrossover.setRange(100.f, 12000.f, 1.f);
    midCrossover.setBounds(250, 220, 100, 60);
    addAndMakeVisible(midCrossover);
    
    gainKnobHiMid.addListener(this);
    gainKnobHiMid.setBounds(320, 60, 100, 90);
    gainKnobHiMid.setValue(audioProcessor.gainHiMid);
    gainKnobHiMid.setRange(0.f, 4.f, .1f);
    gainKnobHiMid.setSkewFactorFromMidPoint(1.f);
    gainKnobHiMid.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobHiMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobHiMid);
    
    hiMidGainLabel.setText("Gain Hi-Mid", juce::dontSendNotification);
    hiMidGainLabel.attachToComponent(&gainKnobHiMid, false);
    addAndMakeVisible(hiMidGainLabel);
    
    distortionTypeHiMid.addListener(this);
    distortionTypeHiMid.addItem("Full Wave", 1);
    distortionTypeHiMid.addItem("Half Wave", 2);
    distortionTypeHiMid.addItem("Hard Clip", 3);
    distortionTypeHiMid.addItem("Cubic", 4);
    distortionTypeHiMid.addItem("arctan", 5);
    distortionTypeHiMid.setSelectedId(3);
    distortionTypeHiMid.setBounds(320, 160, 100, 20);
    addAndMakeVisible(distortionTypeHiMid);
    
    hiMidBandOff.addListener(this);
    hiMidBandOff.setBounds(330, 200, 80, 15);
    hiMidBandOff.setToggleState(audioProcessor.hiMidBandOff, dontSendNotification);
    hiMidBandOff.setButtonText("Band Off");
    addAndMakeVisible(hiMidBandOff);
    
    midHighCrossover.addListener(this);
    midHighCrossover.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    midHighCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    midHighCrossover.setTextValueSuffix(" Hz");
    midHighCrossover.setValue(audioProcessor.midHighCrossover);
    midHighCrossover.setRange(800.f, 20000.f, 1.f);
    midHighCrossover.setBounds(400, 220, 100, 60);
    addAndMakeVisible(midHighCrossover);
    
    gainKnobHigh.addListener(this);
    gainKnobHigh.setBounds(460, 40, 100, 90);
    gainKnobHigh.setValue(audioProcessor.gainHigh);
    gainKnobHigh.setRange(0.f, 4.f, .1f);
    gainKnobHigh.setSkewFactorFromMidPoint(1.f);
    gainKnobHigh.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobHigh.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobHigh);
    
    highGainLabel.setText("Gain High", juce::dontSendNotification);
    highGainLabel.attachToComponent(&gainKnobHigh, false);
    addAndMakeVisible(highGainLabel);
    
    distortionTypeHigh.addListener(this);
    distortionTypeHigh.addItem("Full Wave", 1);
    distortionTypeHigh.addItem("Half Wave", 2);
    distortionTypeHigh.addItem("Hard Clip", 3);
    distortionTypeHigh.addItem("Cubic", 4);
    distortionTypeHigh.addItem("arctan", 5);
    distortionTypeHigh.setSelectedId(5);
    distortionTypeHigh.setBounds(460, 140, 100, 20);
    addAndMakeVisible(distortionTypeHigh);
    
    highBandOff.addListener(this);
    highBandOff.setBounds(470, 200, 80, 15);
    highBandOff.setToggleState(audioProcessor.highBandOff, dontSendNotification);
    highBandOff.setButtonText("Band Off");
    addAndMakeVisible(highBandOff);
    
    mixKnob.addListener(this);
    mixKnob.setBounds(650, 100, 100, 90);
    mixKnob.setValue(audioProcessor.mix);
    mixKnob.setRange(0.f, 100.f, 1.f);
    mixKnob.setTextBoxStyle(Slider::TextBoxRight, false, 40, 20);
    mixKnob.setTextValueSuffix(" %");
    mixKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(mixKnob);
    
    mixLabel.setText("Wet/Dry", juce::dontSendNotification);
    mixLabel.attachToComponent(&mixKnob, false);
    addAndMakeVisible(mixLabel);
    
}

MultiDistortionAudioProcessorEditor::~MultiDistortionAudioProcessorEditor()
{
}

//==============================================================================
void MultiDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::dimgrey);
    
    
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Multiband Distortion", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText("Multiband Distortion", 10, 10, 200, 5, juce::Justification::topLeft, 1);
}

void MultiDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MultiDistortionAudioProcessorEditor::sliderValueChanged(Slider *slider){
    
}

void MultiDistortionAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox){
    
}

void MultiDistortionAudioProcessorEditor::buttonClicked(Button *button){
    
}
