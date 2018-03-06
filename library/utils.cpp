#include "utils.h"
#include "settings.h"
#include <cmath>

int samples(float seconds)
{
    return std::ceil(seconds * LYT_SETTINGS.sampleRate);
}

float seconds(int samples)
{
    return (float)samples / LYT_SETTINGS.sampleRate;
}
