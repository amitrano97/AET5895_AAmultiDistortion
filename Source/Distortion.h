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
    
    // constructor
    Distortion();
    
    void processSignal(float * signal, const int numSamples, const int c);
    
    
    
private:
    
    float Fs = 48000.f;
    
    
};

