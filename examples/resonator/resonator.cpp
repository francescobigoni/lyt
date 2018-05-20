#include <lyt/lyt.h>

int main(int argc, char **argv)
{
    double sampleRate = 44100;
    auto buf = Buffer::zero(44100 * 4);
    auto len = 1.0 / 440.0 * sampleRate;
    Resonator resonator(440, 4.0, 0.01, sampleRate);
    resonator.setState(0.0, 2500.0);

    buf.maps([&](int n, float v)
    {
        double y = resonator.next();
        return y;
    });

    buf.writeFile("output.wav");

    return 0;
}