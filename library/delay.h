#pragma once
#include <vector>
#include "processor.h"

/** The `Delay` class represents a sample-based delay line.
*/
class Delay : public Processor
{
    public:
    /** Constructs a new `Delay` object with a delay time of
        `n` samples.
    
        @param  n           The length of the delay line in samples.
    */
    Delay(int n);

    /** Writes the `value` to the delay line and returns a sample
        from the past (`n` samples ago).

        @param  value       The input sample to delay.     
    */
    virtual float process(float value);

    private:
    int index;
    std::vector<float> vec;
};
