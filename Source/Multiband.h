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
    
    float filterLow(float x, int c);
    float filterLowMid(float x, int c);
    float filterHighMid(float x, int c);
    float filterHigh(float x, int c);
    
    void setCutoffFreqLow(float freq);
    void setCutoffFreqLowMid(float freqLower, float freqUpper);
    void setCutoffFreqHighMid(float freqLower, float freqUpper);
    void setCutoffFreqHigh(float freq);
    
private:
    
    // Two butterworth filters in series for each band to ensure flat response
    Biquad lowFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
    
    
    Biquad lowMidFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
    Biquad lowMidFilter2 = Biquad(Biquad::FilterType::HPF,0.7071f);
    
    Biquad highMidFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
    Biquad highMidFilter2 = Biquad(Biquad::FilterType::HPF,0.7071f);
    
    Biquad highFilter = Biquad(Biquad::FilterType::HPF,0.7071f);
    
    
    
    
};

