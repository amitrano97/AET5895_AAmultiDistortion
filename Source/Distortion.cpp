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

void Distortion::processSignal(float *signal, const int numSamples, const int c){
    
    for (int n = 0; n < numSamples; n++){
        float x = signal[n]; // get value at memory location
        x = processSample(x, gain, thresh, distortionType, c);
        signal[n] = x;
    }
}

void Distortion::setGain(float newGain){
    float gain = newGain;
}

void setThresh (float newThresh){
    float thresh = newThresh;
}

float Distortion::processSample(float x, float gain, float thresh, enum DistortionType, int c){
    
    if (distortionType == FULLWAVE){
        x *= gain;
        float y = abs(x);
        
        return y;
    }
    else if (distortionType == HALFWAVE){
        x *= gain;
        if (x < 0.f)
        {
            float y = 0.f;
            return y;
        }
        else
        {
            float y = x;
            return y;
        }
    }
    else if (distortionType == HARDCLIP){
        x *= gain;
        if (x > thresh)
        {
            float y = thresh;
            return y;
        }
        else if (x < -thresh)
        {
            float y = -thresh;
            return y;
        }
        else
        {
            float y = x;
            return y;
        }
    }
    else if (distortionType == ATAN){
        x *= gain;
        float y = (2.f/M_PI) * atan(gain * x);
        return y;
    }
    else if (distortionType == CUBIC){
        x *= gain;
        float y = x - (1/3)*(x*x*x);
        return y;
    }
//    Haven't added BitCrush yet.
//    else if (distortionType == BIT){
//        
//    }
    
}

void Distortion::setDistortionType(DistortionType newDistortionType){

    distortionType = newDistortionType;

    switch (distortionType) {
        case FULLWAVE:
            distortionType = FULLWAVE;
            break;

        case HALFWAVE:
            distortionType = HALFWAVE;
            break;

        case HARDCLIP:
            distortionType = HARDCLIP;
            break;

        case ATAN:
            distortionType = ATAN;
            break;

        case CUBIC:
            distortionType = CUBIC;
            break;

        //case BIT:
            //    distortionType = BIT;
            //break;

        default:
            newDistortionType = ATAN;
            break;
    }


}


