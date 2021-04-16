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
    
    enum DistortionType { FULLWAVE, HALFWAVE, HARDCLIP, ATAN, CUBIC };
    
//    void processSignal(float * signal, const int numSamples, const int c);
    void setDistortionType (DistortionType newDistortionType);
    
    float processSample(float x, int c);
    
    void setDistType (int newDistType);
    void setThresh (float newThresh);
    void setGain (float newGain);
    

private:
    
    float thresh = 0.7f;
    
    float gain = 0.f;
    
    float Fs = 48000.f;
    
    int distType = 1; // 1 = Fullwave, 2 = halfwave, 3 = hardclip, 4 = ATAN, 5 = Cubic
    
    DistortionType distortionType = FULLWAVE;
    
    
    
};

