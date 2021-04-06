/*
  ==============================================================================

    MultiBand.cpp
    Created: 24 Mar 2021 1:33:34pm
    Author:  Aaron Amitrano

  ==============================================================================
*/

#include "Multiband.h"


// Constructor
Multiband::Multiband(){}


// Apply applicable filters to each frequency band
float Multiband::filterLow(float x, int c){
    // two LPFs in series to make flat response between filters
    float xLow1 = lowFilter.processSample(x,c);
    float xLow = lowFilter.processSample(xLow1,c);
    
    return xLow;
}

float Multiband::filterLowMid(float x, int c){
    float xLowMid1 = lowMidFilter.processSample(x,c);
    float xLowMid = lowMidFilter2.processSample(xLowMid1,c);
    
    return xLowMid;
}

float Multiband::filterHighMid(float x, int c){
    float xHighMid1 = highMidFilter.processSample(x,c);
    float xHighMid = highMidFilter2.processSample(xHighMid1,c);
    
    return xHighMid;
}

float Multiband::filterHigh(float x, int c){
    // Two HPFs in series to make flat response between filters
    float xHigh1 = highFilter.processSample(x,c);
    float xHigh = highFilter.processSample(xHigh1,c);
    
    return xHigh;
}


void Multiband::setCutoffFreqLow(float freq){
    lowFilter.setFreq(freq);
}

void Multiband::setCutoffFreqLowMid(float freqLower, float freqUpper){
//    float freq = (freqLower + freqUpper)/2;
    
    lowMidFilter.setFreq(freqLower);
    lowMidFilter2.setFreq(freqUpper);
}

void Multiband::setCutoffFreqHighMid(float freqLower, float freqUpper){
//    float freq = (freqLower + freqUpper)/2;
    
    highMidFilter.setFreq(freqLower);
    highMidFilter2.setFreq(freqUpper);
}

void Multiband::setCutoffFreqHigh(float freq){
    highFilter.setFreq(freq);
}

