#include "delay.h"

Delay::Delay(int n)
{
    vec.resize(n, 0);
    index = 0;
}

float Delay::process(float value)
{
    int i = index % vec.size();
    float result = vec[i];
    vec[i] = value;
    index += 1;
    return result;
}
