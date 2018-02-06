#include "runningAverage.h"

RunningAverage::RunningAverage()
{
    setCoef(1.0);
}

RunningAverage::RunningAverage(float a)
{
    this->a = a;
    prev = 0;
}

void RunningAverage::setCoef(float a)
{
    this-> a = a;
}

float RunningAverage::process(float x)
{
    float y = a * x + (1.0 - a) * prev;
    prev = y;

    return y;
};
