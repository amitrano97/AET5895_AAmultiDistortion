/*
  ==============================================================================

    MultiBand.h
    Created: 24 Mar 2021 1:33:34pm
    Author:  Aaron Amitrano

  ==============================================================================
*/

#pragma once

#include "Biquad.h"

class Multiband{
    // This class will use biquad to split signals into the necessary frequency bands to apply processing.
public:
    
    Multiband();
    
//    void processSignal(float * signal, const int numSamples, const int c);
//    
    float filterLow(float x, int c);
    float filterLowMid(float x, int c);
    float filterHighMid(float x, int c);
    float filterHigh(float x, int c);
    
    void setCutoffFreqLow(float freq);
    void setCutoffFreqLowMid(float freqLower, float freqUpper);
    void setCutoffFreqHighMid(float freqLower, float freqUpper);
    void setCutoffFreqHigh(float freq);
    
    void prepare(float newFs);
    
private:
    
    float Fs = 48000.f;
    
    // Two butterworth filters in series to create Linkwitz-Riley
    Biquad lowFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
    Biquad lowFilter2 = Biquad(Biquad::FilterType::LPF,0.7071f);
    
    Biquad lowMidFilter = Biquad(Biquad::FilterType::HPF,0.7071f);
    Biquad lowMidFilter2 = Biquad(Biquad::FilterType::HPF,0.7071f);
    Biquad lowMidFilter3 = Biquad(Biquad::FilterType::LPF,0.7071f);
    Biquad lowMidFilter4 = Biquad(Biquad::FilterType::LPF,0.7071f);
    
    Biquad highMidFilter = Biquad(Biquad::FilterType::HPF,0.7071f);
    Biquad highMidFilter2 = Biquad(Biquad::FilterType::HPF,0.7071f);
    Biquad highMidFilter3 = Biquad(Biquad::FilterType::LPF,0.7071f);
    Biquad highMidFilter4 = Biquad(Biquad::FilterType::LPF,0.7071f);
    
    Biquad highFilter = Biquad(Biquad::FilterType::HPF,0.7071f);
    Biquad highFilter2 = Biquad(Biquad::FilterType::HPF,0.7071f);
    

};

