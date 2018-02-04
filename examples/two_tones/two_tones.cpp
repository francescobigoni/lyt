#include <cmath>
#include <lyt/lyt.h>

int main(int argc, char **argv)
{
    auto bufA3 = Buffer::zero(44100);
    auto bufE4 = Buffer::zero(44100);

    bufA3.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * t * 220.0);
    });

    bufE4.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * t * 326.63);
    });

    bufA3.append(bufE4);
    bufA3.writeFile("output.wav");
    return 0;
}
