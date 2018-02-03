#include <iostream>
#include <lyt/buffer.h>
#include <cmath>

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100, 44100); 
    buf.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * t * 440.0);
    });

    buf.writeFile("A440.wav");
    return 0;
}
