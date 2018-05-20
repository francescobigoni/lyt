#include "utils.h"
#include "settings.h"
#include <cmath>
#include <cstdlib>

double pi = 3.14159265359;

int samples(float seconds)
{
    return std::ceil(seconds * LYT_SETTINGS.sampleRate);
}

float seconds(int samples)
{
    return (float)samples / LYT_SETTINGS.sampleRate;
}

float randNum()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float noteToFreq(int note)
{
    float c = std::pow(2, 1.0 / 12.0);
    return std::pow(c, note - 69) * 440;
}
