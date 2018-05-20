#include "fdelay.h"
#include "settings.h"

#include <cmath>
#include <vector>
#include <iostream>

FDelay::FDelay()
{
	setMaxDelay(1);
	setDelay(1);
}

FDelay::FDelay(int maxDelay, float delay)
{
	setMaxDelay(maxDelay);
	setDelay(delay);
}

void FDelay::setMaxDelay(int newMaxDelay)
{
	vec.resize(newMaxDelay + 4, 0);
}

void FDelay::setDelay(float newDelay)
{
	this->delay = newDelay;
	d0 = std::floor(delay);
	d1 = std::ceil(delay);
	d2 = d1 + 1;
	d3 = d1 + 2;

	frac = delay - d0;
}

float FDelay::process(float value)
{
	float y0 = vec[(index - d0) % vec.size()];
	float y1 = vec[(index - d1) % vec.size()];
	float y2 = vec[(index - d2) % vec.size()];
	float y3 = vec[(index - d3) % vec.size()];
	float x = frac;

    float y = 
    	(          (x - 1) * (x - 2) * (x - 3)) / (          (0 - 1) * (0 - 2) * (0 - 3)) * y0 +
        ((x - 0)           * (x - 2) * (x - 3)) / ((1 - 0)           * (1 - 2) * (1 - 3)) * y1 +
        ((x - 0) * (x - 1) *           (x - 3)) / ((2 - 0) * (2 - 1)           * (2 - 3)) * y2 +
        ((x - 0) * (x - 1) * (x - 2)          ) / ((3 - 0) * (3 - 1) * (3 - 2)          ) * y3;

    vec[index % vec.size()] = value;
    index += 1;

    return y;
}