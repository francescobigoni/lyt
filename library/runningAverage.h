#pragma once
#include "processor.h"

/** The RunningAverage class implements a simple two-point running
    average algorithm:
        
        y[n] = a * x[n] + (1 - a) * y[n - 1]
*/
class RunningAverage : public Processor
{
    public:
    /** Initializes a new `RunningAverage` with coefficient 1.0.
    */
    RunningAverage();

    /** Initializes a new `RunningAverage` with coefficient `a`.

        @param  a       The amount of *new* data going into the filter.
    */
    RunningAverage(float a);

    /** Sets the coefficient of the algorithm.

        @param  a       The amount of *new* data going into the filter.
    */
    void setCoef(float a);

    /** Takes one input sample and returns the processed sample.
        
        @param  x       The sample to process.
    */
    virtual float process(float x);

    private:
    float a;
    float prev;
};
