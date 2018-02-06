#include <iostream>
#include <cstdlib>
#include <lyt/lyt.h>
#include <cmath>

float randFloat()
{
    float f = ((double) rand() / (RAND_MAX)) + 1;
    return (f * 2.0) - 1.0;
}

float mapRange(float x, float oldMin, float oldMax, float newMin, float newMax)
{
    float r = (x - oldMin) / (oldMax - oldMin);
    return newMin + r * (newMax - newMin);
}

struct RunningAvgerage
{
    RunningAvgerage(float a)
    {
        this->a = a;
        prev = 0;
    }

    float process(float x)
    {
        float y = a * x + (1.0 - a) * prev;
        prev = y;
        return y;
    };

    float a;
    float prev;
};

float reed(float mouthPressure, float borePressure)
{
    float deltaPressure = borePressure - mouthPressure;
    float alpha = mapRange(deltaPressure, -0.1, 1.8, 1.0, 0.0);

    if (deltaPressure < -0.1)
        alpha = 1.0;

    return alpha * borePressure + (1.0 - alpha) * mouthPressure;
}

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100 * 5); 
    auto boreDelay = Delay::Delay(LYT_SETTINGS.sampleRate / 440);
    auto reflectLpf = RunningAvgerage::RunningAvgerage(0.9);
    float mouthPressure = 0.09;

    buf.mapt([&](float t, float v)
    {
        if (t > 2.0)
            mouthPressure = 0.0;

        float borePressure = boreDelay.read();
        float r = reed(mouthPressure, borePressure);
        boreDelay.write(reflectLpf.process(-r));
        return borePressure;
    });

    buf.writeFile("output.wav");
    return 0;
}
