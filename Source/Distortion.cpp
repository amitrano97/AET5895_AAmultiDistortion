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
    
    
    
}

void Distortion::setDistortionType(DistortionType newDitortionType){
    
    distortionType = newDitortionType;
    
    switch (distortionType) {
        case FULLWAVE:
            
            break;
        
        case HALFWAVE:
            
            break;
            
        case HARDCLIP:
            
            break;
            
        case ATAN:
            
            break;
            
        case CUBIC:
            
            break;
        
        case BIT:
            
            break;
            
        default:
            
            break;
    }
    
    
}


