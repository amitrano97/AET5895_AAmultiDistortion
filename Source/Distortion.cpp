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
    gain = newGain;
}

void Distortion::setThresh(float newThresh){
    thresh = newThresh;
}

void Distortion::setDistortionType(int newDistortionType){
    distType = newDistortionType;
}

float Distortion::processSample(float x, float gain, float thresh, int distType, int c){
    
    if (distType == 1){
        x *= gain;
        float y = abs(x);
        
        return y;
    }
    else if (distType == 2){
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
    else if (distType == 3){
        x *= gain;
        if (x > thresh)
        {
            float y = thresh;
            return y;
        }
        else if (x < (-1.f * thresh))
        {
            float y = -1.f * thresh;
            return y;
        }
        else
        {
            float y = x;
            return y;
        }
    }
    else if (distType == 4){
        x *= gain;
        float y = (2.f/M_PI) * atan(gain * x);
        return y;
    }
    else if (distType == 5){
        x *= gain;
        float y = x - ((1/3)*(x*x*x));
        return y;
    }
//    //Haven't added BitCrush yet.
//    else if (distortionType == 6){
//        
//    }
    
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

//        case BIT:
//                distortionType = BIT;
//            break;

//        default:
//            newDistortionType = ATAN;
//            break;
    }
}


