#pragma once
#include "processor.h"

enum FilterType
{
    LowPass
};

class Biquad : public Processor
{
    public:
    /** Creates a new biquad filter object

        @param  sampleRate      The sample rate of the input signal (optional).
    */
    Biquad(float sampleRate = 0);

    /** Creates a new biquad filter in low-pass configuration.

        @param  freq            The cutoff frequency.
        @param  q               The filter quality/sharpness.
        @param  sampleRate      The sample rate of the input signal (optional).
    */
    static Biquad LowPass(float freq, float q, float sampleRate = 0);

    /** Resets the memory of the filter.
    */
    void reset();

    /** Sets the internal coefficients of the filter.

        @param  type            The configuration of the filter.
        @param  freq            The cutoff frequency.
        @param  q               The filter quality/sharpness.
    */
    void setCoefs(FilterType type, float freq, float q);

    /** Filters a single sample of the input signal.
    */
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
