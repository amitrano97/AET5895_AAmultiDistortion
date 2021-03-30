/*
  ==============================================================================

    MultiBand.h
    Created: 24 Mar 2021 1:33:34pm
    Author:  Aaron Amitrano

  ==============================================================================
*/

#pragma once

#include "Biquad.h"
#include "PluginEditor.h"

// This class will use biquad to split the signal into the necessary frequency bands to apply processing.

class Multiband{
public:
    
    void processSignal(float * signal, const int numSamples, const int c);
    
    void setCutoffFreqLowMid(float freq);
    void setCutoffFreqMid(float freq);
    void setCutoffFreqMidHigh(float freq);

    
private:
    
    // Two butterworth filters in series for each band to ensure flat response
    Biquad lowFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
    Biquad lowFilter2 = Biquad(Biquad::FilterType::LPF,0.7071f);
    
    Biquad lowMidFilter = Biquad(Biquad::FilterType::BPF1,0.7071f);
    Biquad lowMidFilter2 = Biquad(Biquad::FilterType::BPF1,0.7071f);
    
    Biquad HighMidFilter = Biquad(Biquad::FilterType::BPF1,0.7071f);
    Biquad HighMidFilter2 = Biquad(Biquad::FilterType::BPF1,0.7071f);
    
    Biquad HighFilter = Biquad(Biquad::FilterType::HPF,0.7071f);
    Biquad HighFilter2 = Biquad(Biquad::FilterType::HPF,0.7071f);
    
    
    
};

