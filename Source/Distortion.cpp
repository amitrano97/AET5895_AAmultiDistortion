/*
  ==============================================================================

    Distortion.cpp
    Created: 2 Mar 2021 1:41:23pm
    Author:  Aaron Amitrano

  ==============================================================================
*/

#include "Distortion.h"


// Constructor
Distortion::Distortion(){}

//void Distortion::processSignal(float *signal, const int numSamples, const int c){
//
//    for (int n = 0; n < numSamples; n++){
//        float x = signal[n]; // get value at memory location
//        x = processSample(x, gain, thresh, distortionType, c);
//        signal[n] = x;
//    }
//}

float Distortion::processSample(float x, int c){
    
    float y = x;
    
    if (distType == 1){
        x *= gain;
        y = abs(x);
    }
    else if (distType == 2){
        x *= gain;
        if (x < 0.f)
        {
            y = 0.f;
        }
        else
        {
            y = x;
        }
    }
    else if (distType == 3){
        x *= gain;
        if (x > thresh)
        {
            y = thresh;
        }
        else if (x < (-1.f * thresh))
        {
            y = -1.f * thresh;
        }
        else
        {
            y = x;
        }
    }
    else if (distType == 4){
        x *= gain;
        y = (2.f/M_PI) * atan(gain * x);
    }
    else if (distType == 5){
        x *= gain;
        y = x - ((1.f/3.f)*(x*x*x));
    }
    
    return y;
}

void Distortion::setDistortionType(DistortionType newDistortionType){
    
    distortionType = newDistortionType;
    
    switch (distortionType) {
        case FULLWAVE:
            distType = 1;
            break;
            
        case HALFWAVE:
            distType = 2;
            break;
            
        case HARDCLIP:
            distType = 3;
            break;
            
        case ATAN:
            distType = 4;
            break;
            
        case CUBIC:
            distType = 5;
            break;
            
        default:
            distType = 1;
            break;
    }
    
    setDistType(distType);
    
}

void Distortion::setDistType(int newDistType){
    distType = newDistType;
}

void Distortion::setThresh(float newThresh){
    
    thresh = newThresh;
    
}

void Distortion::setGain(float newGain){
    
    gain = pow(10.f, newGain/20.f);
    
}

