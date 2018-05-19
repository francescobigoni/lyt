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
	vec.resize(newMaxDelay, 0);
}

void FDelay::setDelay(float newDelay)
{
	this->delay = newDelay;
	lowerDelay = std::floor(delay);
	upperDelay = std::ceil(delay);
	frac = upperDelay - delay;
	std::cout << "delay = " << newDelay << std::endl;
	std::cout << "lower = " << lowerDelay << std::endl;
	std::cout << "upper = " << upperDelay << std::endl;
	std::cout << "frac = " << frac << std::endl;
}

float FDelay::process(float value)
{
    float lower = vec[(index - upperDelay) % vec.size()];
    float upper = vec[(index - lowerDelay) % vec.size()];
    float y = lower + frac * (upper - lower);

    vec[index % vec.size()] = value;
    index += 1;

    return y;
}