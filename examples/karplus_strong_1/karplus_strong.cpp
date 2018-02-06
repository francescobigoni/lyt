#include <iostream>
#include <cstdlib>
#include <lyt/lyt.h>
#include <cmath>

float randFloat()
{
    return ((double) rand() / (RAND_MAX)) + 1;
}

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100 * 5); 
    auto del = Delay::Delay(LYT_SETTINGS.sampleRate / 440);
    float a = 0.2;
    float d_prev = 0;

    buf.mapt([&](float t, float v)
    {
        float pluck = 0;

        if (t < 0.03)
             pluck = 0.8 * randFloat();

        float d = a * d_prev + (1.0 - a) * del.read();
        d_prev = d;
        float i = pluck + d;
        del.write(i);

        return d;
    });

    buf.writeFile("output.wav");
    return 0;
}
