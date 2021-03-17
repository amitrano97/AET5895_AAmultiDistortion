/*
  ==============================================================================

    Distortion.h
    Created: 2 Mar 2021 1:41:23pm
    Author:  Aaron Amitrano

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Distortion{
    
public:
    
    Distortion();
    
    enum DistortionType { FULLWAVE, HALFWAVE, HARDCLIP, ATAN, CUBIC };
    
    void processSignal(float * signal, const int numSamples, const int c);
    
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    

    
private:
    
    float Fs = 48000.f;
    
    DistortionType distortionType = ATAN;
    
    
};

