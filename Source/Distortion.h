/*
  ==============================================================================

    Distortion.h
    Created: 2 Mar 2021 1:41:23pm
    Author:  Aaron Amitrano

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Multiband.h"
#include <math.h>

class Distortion{
    
public:
    
    Distortion();
    
    enum DistortionType { FULLWAVE, HALFWAVE, HARDCLIP, ATAN, CUBIC, BIT };
    
    void processSignal(float * signal, const int numSamples, const int c);
    void setDistortionType (DistortionType newDistortionType);
    
    float processSample(float x, float gain, float thresh, int distType, int c);
    
    void setDistortionType (int newDistortionType);
    void setThresh (float newThresh);
    void setGain (float newGain);
    

private:
    
    float thresh = 0.7f;
    
    float gain = 1.f;
    
    float Fs = 48000.f;
    
    int distType = 1; // 1 = Fullwave, 2 = halfwave, 3 = hardclip, 4 = ATAN, 5 = Cubic
    
    DistortionType distortionType = ATAN;
    
    
    
};

