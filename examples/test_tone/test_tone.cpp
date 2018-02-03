#include <iostream>
#include <lyt/buffer.h>
#include <cmath>

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100, 44100); 
    /*
    for (int i = 0; i < buf.numSamples(); i++)
    {
        float t = (float)i / 44100;
        buf.set(i, std::sin(2 * M_PI * t * 440.0));
    }
    */
    buf.mapt([&](float t, float v)
    {
        // std::cout << t << std::endl;
        return std::sin(2 * M_PI * t * 440.0);
    });

    buf.writeFile("A440.wav");
    return 0;
}
