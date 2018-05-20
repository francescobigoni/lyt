#include "resonator.h"

#include <cmath>

#include "utils.h"

Resonator::Resonator()
{
    f = 0.0;
    u0 = 0.0;
    u1 = 0.0;
    setParams(440, 1.0, 0.01, 44100);
}

Resonator::Resonator(double freq, double decay, double mass, double sampleRate)
{
    f = 0.0;
    u0 = 0.0;
    u1 = 0.0;
    setParams(freq, decay, mass, sampleRate);
}

void Resonator::setParams(double freq, double decay, double mass, double sampleRate)
{
    using namespace std;

    k = 1.0 / sampleRate;
    w = 2.0 * pi * freq;
    m = mass;
    g = (2.0 * log(1000)) / decay;
    a = 1.0 / (1.0 / pow(k, 2.0) + g / (2.0 * k));
    b = 2.0 / pow(k, 2.0) - pow(w, 2.0);
    c = g / (2.0 * k) - 1.0 / pow(k, 2.0);
}

void Resonator::setState(double displacement, double velocity)
{
    u0 = displacement;
    u1 = u0 + k * velocity;
}

void Resonator::setForce(double force)
{
    f = force;
}

double Resonator::next()
{
    double ut = a * b * u0 + a * c * u1 + a * (f / m);
    u1 = u0;
    u0 = ut;

    return u0;
}