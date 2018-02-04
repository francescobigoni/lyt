#include <cmath>
#include <lyt/lyt.h>

int samples(float seconds)
{
    return std::ceil(seconds * LYT_SETTINGS.sampleRate);
}

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(samples(5.0));
    Delay delay(samples(0.15));

    buf.mapt([&](float t, float v)
    {   
        if (t < 0.05)
            v = std::sin(2 * M_PI * t * 440.0);

        v = v + delay.read();
        delay.write(v * 0.8);
        return v;
    });

    buf.writeFile("output.wav");

    return 0;
}
