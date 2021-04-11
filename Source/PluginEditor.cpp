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
    gainKnobLow.setValue(*audioProcessor.gainLow);
    gainKnobLow.setRange(1.f, 10.f, .1f);
    //gainKnobLow.setSkewFactorFromMidPoint(1.f);
    gainKnobLow.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobLow.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobLow);
    
    lowGainLabel.setText("Gain Low", juce::dontSendNotification);
    lowGainLabel.attachToComponent(&gainKnobLow, false);
    lowGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lowGainLabel);
    
    distortionTypeLow.addListener(this);
    distortionTypeLow.addItem("Full Wave", 1);
    distortionTypeLow.addItem("Half Wave", 2);
    distortionTypeLow.addItem("Hard Clip", 3);
    distortionTypeLow.addItem("Cubic", 4);
    distortionTypeLow.addItem("arctan", 5);
    distortionTypeLow.setSelectedId(audioProcessor.distortionTypeLow);
    distortionTypeLow.setBounds(40, 160, 100, 20);
    addAndMakeVisible(distortionTypeLow);
    
    lowBandOff.addListener(this);
    lowBandOff.setBounds(50, 200, 80, 15);
    lowBandOff.setToggleState(audioProcessor.lowBandisOff, dontSendNotification);
    lowBandOff.setButtonText("Band Off");
    addAndMakeVisible(lowBandOff);
    
    lowMidCrossover.addListener(this);
    lowMidCrossover.setValue(audioProcessor.lowMidCrossoverFreq);
    lowMidCrossover.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lowMidCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    lowMidCrossover.setTextValueSuffix(" Hz");
    lowMidCrossover.setRange(20.f, 349.f, 1.f);
    lowMidCrossover.setBounds(100, 220, 100, 60);
    addAndMakeVisible(lowMidCrossover);
    
    gainKnobMid.addListener(this);
    gainKnobMid.setBounds(180, 40, 100, 90);
    gainKnobMid.setValue(audioProcessor.gainMid);
    gainKnobMid.setRange(1.f, 10.f, .1f);
    //gainKnobMid.setSkewFactorFromMidPoint(5.f);
    gainKnobMid.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobMid);
    
    midGainLabel.setText("Gain Mid", juce::dontSendNotification);
    midGainLabel.attachToComponent(&gainKnobMid, false);
    midGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(midGainLabel);
    
    distortionTypeMid.addListener(this);
    distortionTypeMid.addItem("Full Wave", 1);
    distortionTypeMid.addItem("Half Wave", 2);
    distortionTypeMid.addItem("Hard Clip", 3);
    distortionTypeMid.addItem("Cubic", 4);
    distortionTypeMid.addItem("arctan", 5);
    distortionTypeMid.setSelectedId(audioProcessor.distortionTypeMid);
    distortionTypeMid.setBounds(180, 140, 100, 20);
    addAndMakeVisible(distortionTypeMid);
    
    midBandOff.addListener(this);
    midBandOff.setBounds(190, 200, 80, 15);
    midBandOff.setToggleState(audioProcessor.midBandisOff, dontSendNotification);
    midBandOff.setButtonText("Band Off");
    addAndMakeVisible(midBandOff);
    
    midCrossover.addListener(this);
    midCrossover.setValue(audioProcessor.midCrossoverFreq);
    midCrossover.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    midCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    midCrossover.setTextValueSuffix(" Hz");
    midCrossover.setRange(350.f, 4999.f, 1.f);
    midCrossover.setBounds(250, 220, 100, 60);
    addAndMakeVisible(midCrossover);
    
    gainKnobHiMid.addListener(this);
    gainKnobHiMid.setBounds(320, 60, 100, 90);
    gainKnobHiMid.setValue(audioProcessor.gainHiMid);
    gainKnobHiMid.setRange(1.f, 10.f, .1f);
    //gainKnobHiMid.setSkewFactorFromMidPoint(1.f);
    gainKnobHiMid.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobHiMid.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobHiMid);
    
    hiMidGainLabel.setText("Gain Hi-Mid", juce::dontSendNotification);
    hiMidGainLabel.attachToComponent(&gainKnobHiMid, false);
    hiMidGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(hiMidGainLabel);
    
    distortionTypeHiMid.addListener(this);
    distortionTypeHiMid.addItem("Full Wave", 1);
    distortionTypeHiMid.addItem("Half Wave", 2);
    distortionTypeHiMid.addItem("Hard Clip", 3);
    distortionTypeHiMid.addItem("Cubic", 4);
    distortionTypeHiMid.addItem("arctan", 5);
    distortionTypeHiMid.setSelectedId(audioProcessor.distortionTypeHiMid);
    distortionTypeHiMid.setBounds(320, 160, 100, 20);
    addAndMakeVisible(distortionTypeHiMid);
    
    hiMidBandOff.addListener(this);
    hiMidBandOff.setBounds(330, 200, 80, 15);
    hiMidBandOff.setToggleState(audioProcessor.hiMidBandisOff, dontSendNotification);
    hiMidBandOff.setButtonText("Band Off");
    addAndMakeVisible(hiMidBandOff);
    
    midHighCrossover.addListener(this);
    midHighCrossover.setValue(audioProcessor.midHighCrossoverFreq);
    midHighCrossover.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    midHighCrossover.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    midHighCrossover.setTextValueSuffix(" Hz");
    midHighCrossover.setRange(5000.f, 20000.f, 1.f);
    midHighCrossover.setBounds(400, 220, 100, 60);
    addAndMakeVisible(midHighCrossover);
    
    gainKnobHigh.addListener(this);
    gainKnobHigh.setBounds(460, 40, 100, 90);
    gainKnobHigh.setValue(audioProcessor.gainHigh);
    gainKnobHigh.setRange(1.f, 10.f, .1f);
    //gainKnobHigh.setSkewFactorFromMidPoint(5.f);
    gainKnobHigh.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    gainKnobHigh.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainKnobHigh);
    
    highGainLabel.setText("Gain High", juce::dontSendNotification);
    highGainLabel.attachToComponent(&gainKnobHigh, false);
    highGainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(highGainLabel);
    
    distortionTypeHigh.addListener(this);
    distortionTypeHigh.addItem("Full Wave", 1);
    distortionTypeHigh.addItem("Half Wave", 2);
    distortionTypeHigh.addItem("Hard Clip", 3);
    distortionTypeHigh.addItem("Cubic", 4);
    distortionTypeHigh.addItem("arctan", 5);
    distortionTypeHigh.setSelectedId(audioProcessor.distortionTypeHigh);
    distortionTypeHigh.setBounds(460, 140, 100, 20);
    addAndMakeVisible(distortionTypeHigh);
    
    highBandOff.addListener(this);
    highBandOff.setBounds(470, 200, 80, 15);
    highBandOff.setToggleState(audioProcessor.highBandisOff, dontSendNotification);
    highBandOff.setButtonText("Band Off");
    addAndMakeVisible(highBandOff);
    
    mixKnob.addListener(this);
    mixKnob.setValue(audioProcessor.mixPerc);
    mixKnob.setBounds(650, 160, 100, 90);
    mixKnob.setRange(0.f, 100.f, 1.f);
    mixKnob.setTextBoxStyle(Slider::TextBoxRight, false, 40, 20);
    mixKnob.setTextValueSuffix(" %");
    mixKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(mixKnob);
    
    mixLabel.setText("Wet/Dry", juce::dontSendNotification);
    mixLabel.attachToComponent(&mixKnob, false);
    addAndMakeVisible(mixLabel);
    
    outputKnob.addListener(this);
    outputKnob.setValue(audioProcessor.outputGain);
    outputKnob.setBounds(650, 40, 110, 90);
    outputKnob.setRange(-24.f, +24.f, 0.1f);
    outputKnob.setTextBoxStyle(Slider::TextBoxRight, false, 50, 20);
    outputKnob.setTextValueSuffix("dB");
    outputKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(outputKnob);
    
    outputLabel.setText("Output Gain", juce::dontSendNotification);
    outputLabel.attachToComponent(&outputKnob, false);
    addAndMakeVisible(outputLabel);
    
    startTimerHz(30);
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
    if (slider == &gainKnobLow){
        *audioProcessor.gainLow = gainKnobLow.getValue();
    }
    else if (slider == &gainKnobMid){
        audioProcessor.gainMid = gainKnobMid.getValue();
    }
    else if (slider == &gainKnobHiMid){
        audioProcessor.gainHiMid = gainKnobHiMid.getValue();
    }
    else if (slider == &gainKnobHigh){
        audioProcessor.gainHigh = gainKnobHigh.getValue();
    }
    else if (slider == &mixKnob){
        audioProcessor.mixPerc = mixKnob.getValue();
    }
    else if (slider == &lowMidCrossover){
        audioProcessor.lowMidCrossoverFreq = lowMidCrossover.getValue();
    }
    else if (slider == &midCrossover){
        audioProcessor.midCrossoverFreq = midCrossover.getValue();
    }
    else if (slider == &midHighCrossover){
        audioProcessor.midHighCrossoverFreq = midHighCrossover.getValue();
    }
}

void MultiDistortionAudioProcessorEditor::comboBoxChanged(ComboBox *comboBox){
    if (comboBox == &distortionTypeLow){
        if (distortionTypeLow.getSelectedId() == 1){
            audioProcessor.distortionTypeLow = Distortion::DistortionType::FULLWAVE;
        }
        if (distortionTypeLow.getSelectedId() == 2){
            audioProcessor.distortionTypeLow = Distortion::DistortionType::HALFWAVE;
        }
        if (distortionTypeLow.getSelectedId() == 3){
            audioProcessor.distortionTypeLow = Distortion::DistortionType::HARDCLIP;
        }
        if (distortionTypeLow.getSelectedId() == 4){
            audioProcessor.distortionTypeLow = Distortion::DistortionType::ATAN;
        }
        if (distortionTypeLow.getSelectedId() == 5){
            audioProcessor.distortionTypeLow = Distortion::DistortionType::CUBIC;
        }
    }
    else if (comboBox == &distortionTypeMid){
        if (distortionTypeMid.getSelectedId() == 1){
            audioProcessor.distortionTypeMid = Distortion::DistortionType::FULLWAVE;
        }
        if (distortionTypeMid.getSelectedId() == 2){
            audioProcessor.distortionTypeMid = Distortion::DistortionType::HALFWAVE;
        }
        if (distortionTypeMid.getSelectedId() == 3){
            audioProcessor.distortionTypeMid = Distortion::DistortionType::HARDCLIP;
        }
        if (distortionTypeMid.getSelectedId() == 4){
            audioProcessor.distortionTypeMid = Distortion::DistortionType::ATAN;
        }
        if (distortionTypeMid.getSelectedId() == 5){
            audioProcessor.distortionTypeMid = Distortion::DistortionType::CUBIC;
        }
    }
    else if (comboBox == &distortionTypeHiMid){
        if (distortionTypeHiMid.getSelectedId() == 1){
            audioProcessor.distortionTypeHiMid = Distortion::DistortionType::FULLWAVE;
        }
        if (distortionTypeHiMid.getSelectedId() == 2){
            audioProcessor.distortionTypeHiMid = Distortion::DistortionType::HALFWAVE;
        }
        if (distortionTypeHiMid.getSelectedId() == 3){
            audioProcessor.distortionTypeHiMid = Distortion::DistortionType::HARDCLIP;
        }
        if (distortionTypeHiMid.getSelectedId() == 4){
            audioProcessor.distortionTypeHiMid = Distortion::DistortionType::ATAN;
        }
        if (distortionTypeHiMid.getSelectedId() == 5){
            audioProcessor.distortionTypeHiMid = Distortion::DistortionType::CUBIC;
        }
    }
    else if (comboBox == &distortionTypeHigh){
        if (distortionTypeHigh.getSelectedId() == 1){
            audioProcessor.distortionTypeHigh = Distortion::DistortionType::FULLWAVE;
        }
        if (distortionTypeMid.getSelectedId() == 2){
            audioProcessor.distortionTypeHigh = Distortion::DistortionType::HALFWAVE;
        }
        if (distortionTypeMid.getSelectedId() == 3){
            audioProcessor.distortionTypeHigh = Distortion::DistortionType::HARDCLIP;
        }
        if (distortionTypeMid.getSelectedId() == 4){
            audioProcessor.distortionTypeHigh = Distortion::DistortionType::ATAN;
        }
        if (distortionTypeMid.getSelectedId() == 5){
            audioProcessor.distortionTypeHigh = Distortion::DistortionType::CUBIC;
        }
    }
}

void MultiDistortionAudioProcessorEditor::buttonClicked(Button *button){
    if (button == &lowBandOff){
        audioProcessor.lowBandisOff = !audioProcessor.lowBandisOff;
    }
    else if (button == &midBandOff){
        audioProcessor.midBandisOff = !audioProcessor.midBandisOff;
    }
    else if (button == &hiMidBandOff){
        audioProcessor.hiMidBandisOff = !audioProcessor.hiMidBandisOff;
    }
    else if (button == &highBandOff){
        audioProcessor.highBandisOff = !audioProcessor.highBandisOff;
    }
}

void MultiDistortionAudioProcessorEditor::timerCallback(){
    gainKnobLow.setValue(*audioProcessor.gainLow);
}

