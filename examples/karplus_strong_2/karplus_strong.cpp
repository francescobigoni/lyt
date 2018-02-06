#include <iostream>
#include <cstdlib>
#include <lyt/lyt.h>
#include <cmath>

float mapRange(float x, float oldMin, float oldMax, float newMin, float newMax)
{
    float r = (x - oldMin) / (oldMax - oldMin);
    return newMin + r * (newMax - newMin);
}

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100 * 5); 
    auto del = Delay::Delay(LYT_SETTINGS.sampleRate / 220);
    float a = 0.7;
    float dPrev = 0;
    float pluckAttack = 0.01;
    float pluckRelease = 0.01;

    buf.mapt([&](float t, float v)
    {
        float pluck = 0;

        if (t <= pluckAttack)
            pluck = mapRange(t, 0, pluckAttack, 0, 1);
        else if (t < pluckAttack + pluckRelease)
            pluck = mapRange(t, pluckAttack, pluckAttack + pluckRelease, 1, 0);
        else
            pluck = 0;

        float r = del.read();
        float d = a * dPrev + (1.0 - a) * r;
        dPrev = d;
        float i = pluck + d;
        del.write(i);

        return r;
    });

    buf.writeFile("output.wav");
    return 0;
}
