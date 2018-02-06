#include "biquad.h"
#include "settings.h"
#include <cmath>

Biquad::Biquad()
{
    sampleRate = LYT_SETTINGS.sampleRate; 
    reset();
}

void Biquad::reset()
{
    x1 = 0.0;
    x2 = 0.0;
    y1 = 0.0;
    y2 = 0.0;
}

void Biquad::setCoefs(FilterType type, float sampleRate, float freq, float q)
{
    float w0 = 2 * M_PI * freq / sampleRate;
    float cosw0 = std::cos(w0);
    float sinw0 = std::sin(w0);
    float alpha = sinw0 / (2.0 * q);
    
    if (type == FilterType::LowPass)
    {
        b0 =  (1.0 - cosw0) / 2.0;
        b1 =  1.0 - cosw0;
        b2 =  (1.0 - cosw0) / 2.0;
        a0 =  1.0 + alpha;
        a1 =  -2.0 * cosw0;
        a2 =  1.0 - alpha;
    }
}

//y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2]
//        - (a1/a0)*y[n-1] - (a2/a0)*y[n-2]            (Eq 4)
float Biquad::process(float x)
{
    float y = (b0 / a0) * x  + (b1 / a0) * x1 + (b2 / a0) * x2
            - (a1 / a0) * y1 - (a2 / a0) * y2;
    y2 = y1;
    y1 = y;
    x2 = x1;
    x1 = x;
    return y;
}
