#include <lyt/lyt.h>
#include <cmath>

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100); 
    buf.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * t * 440.0);
    });

    buf.writeFile("output.wav");
    return 0;
}
