#include <iostream>
#include <cstdlib>
#include <lyt/lyt.h>
#include <cmath>

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

int main(int argc, char **argv)
{
    float a = 0.8;
    float pluckAttack = 0.01;
    float pluckRelease = 0.02;
    float pluckPoint = 0.3;
    float freq = 220;

    int totalLength = LYT_SETTINGS.sampleRate / freq;
    int lengthA = pluckPoint * totalLength;
    int lengthB = (1.0 - pluckPoint) * totalLength;

    auto buf = Buffer::zero(44100 * 5); 
    auto delA = Delay::Delay(lengthA);
    auto lpfA = RunningAvgerage::RunningAvgerage(a);
    auto delB = Delay::Delay(lengthB);
    auto lpfB = RunningAvgerage::RunningAvgerage(a);

    buf.mapt([&](float t, float v)
    {
        float pluck = 0;

        if (t <= pluckAttack)
            pluck = mapRange(t, 0, pluckAttack, 0, 1);
        else if (t < pluckAttack + pluckRelease)
            pluck = mapRange(t, pluckAttack, pluckAttack + pluckRelease, 1, 0);
        else
            pluck = 0;

        float rA = delA.read();
        float rB = delB.read();
        delA.write(pluck + lpfA.process(rB));
        delB.write(pluck + lpfB.process(rA));
        return rA;
    });

    buf.writeFile("output.wav");
    return 0;
}
