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


void Multiband::prepare(float newFs){
    
    Fs = newFs;
    
    lowFilter.setFs(Fs);
    lowFilter2.setFs(Fs);
    lowMidFilter.setFs(Fs);
    lowMidFilter2.setFs(Fs);
    lowMidFilter3.setFs(Fs);
    lowMidFilter4.setFs(Fs);
    highMidFilter.setFs(Fs);
    highMidFilter2.setFs(Fs);
    highMidFilter3.setFs(Fs);
    highMidFilter4.setFs(Fs);
    highFilter.setFs(Fs);
    highFilter2.setFs(Fs);
    
}

// Apply applicable filters to each frequency band
float Multiband::filterLow(float x, int c){
    // two LPFs in series to make flat response @ crossover
    float xLow1 = lowFilter.processSample(x,c);
    float xLow = lowFilter2.processSample(xLow1,c);
    
    return xLow;
}

float Multiband::filterLowMid(float x, int c){
    float xLowMid1 = lowMidFilter.processSample(x,c);
    float xLowMid2 = lowMidFilter2.processSample(xLowMid1,c);
    float xLowMid3 = lowMidFilter3.processSample(xLowMid2,c);
    float xLowMid = lowMidFilter4.processSample(xLowMid3,c);
    
    return xLowMid;
}

float Multiband::filterHighMid(float x, int c){
    float xHighMid1 = highMidFilter.processSample(x,c);
    float xHighMid2 = highMidFilter2.processSample(xHighMid1,c);
    float xHighMid3 = highMidFilter3.processSample(xHighMid2,c);
    float xHighMid = highMidFilter4.processSample(xHighMid3,c);
    
    return xHighMid;
}

float Multiband::filterHigh(float x, int c){
    // Two HPFs in series to make flat response @ crossover
    float xHigh1 = highFilter.processSample(x,c);
    float xHigh = highFilter2.processSample(xHigh1,c);
    
    return xHigh;
}

void Multiband::setCutoffFreqLow(float freq){
    lowFilter.setFreq(freq);
    lowFilter2.setFreq(freq);
}

void Multiband::setCutoffFreqLowMid(float freqLower, float freqUpper){
    
    lowMidFilter.setFreq(freqLower);
    lowMidFilter2.setFreq(freqLower);
    lowMidFilter3.setFreq(freqUpper);
    lowMidFilter4.setFreq(freqUpper);
}

void Multiband::setCutoffFreqHighMid(float freqLower, float freqUpper){
//    float freq = (freqLower + freqUpper)/2;
    
    highMidFilter.setFreq(freqLower);
    highMidFilter2.setFreq(freqLower);
    highMidFilter3.setFreq(freqUpper);
    highMidFilter4.setFreq(freqUpper);
}

void Multiband::setCutoffFreqHigh(float freq){
    highFilter.setFreq(freq);
    highFilter2.setFreq(freq);
}

