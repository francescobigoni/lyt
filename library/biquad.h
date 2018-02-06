#pragma once
#include "processor.h"

enum FilterType
{
    LowPass
};

class Biquad : public Processor
{
public:
    Biquad();
    void reset();
    void setCoefs(FilterType type, float sampleRate, float freq, float q);
    virtual float process(float value);
    
private:
    float sampleRate;
    float x1;
    float x2;
    float y1;
    float y2;
    float a0;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
};
