#pragma once

#include <vector>

#include "processor.h"

// An implementation of a linear interpolation fractional delay line.
class FDelay : public Processor
{
    public:
    /// Constructs a new `FDelay` object with at delay time of
    /// one sample.
    FDelay();

    /// Constructs a new `FDelay` object with a max sample delay time of
    /// `n` samples.
    /// @param  maxDelay    The maximal sample delay time.
    /// @param  delay       The sample delay time.
    FDelay(int maxDelay, float delay);

    // Sets the maximal delay time (in samples). Use `setDelay` to set the
    // actual delay time.
    // @param   newMaxDelay The new maximal sample delay time.
    // @see setDelay()
    void setMaxDelay(int newMaxDelay);

    /// Sets the sample delay time. Must be less than the maximal delay time.
    /// @param  newDelay   The new sample delay time.
    /// @see setMaxDelay()
    void setDelay(float newDelay);

    /// Writes the `value` to the delay line and returns a sample
    /// from the past (`n` samples ago).
    /// @param  value   The input sample to delay.
    virtual float process(float value);

    private:
    int index;
    int lowerDelay;
    int upperDelay;
    float delay;
    float frac;
    std::vector<float> vec;
};