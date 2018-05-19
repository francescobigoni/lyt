#include <lyt/lyt.h>
#include <cmath>

int main(int argc, char **argv)
{
    float fStart = 20;
    float fEnd = 20000;
    float length = 5;

    auto buf1 = Buffer::zero(length * LYT_SETTINGS.sampleRate);
    auto buf2 = Buffer::zero(length * LYT_SETTINGS.sampleRate);

    float kLin = (fEnd - fStart) / length;
    float kExp = std::pow(fEnd / fStart, 1 / length);

    buf1.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * t * (fStart + kLin * t / 2));
    });

    buf2.mapt([&](float t, float v)
    {
        return std::sin(2 * M_PI * fStart * std::pow(kExp, t) / std::log(kExp));
    });

    buf1.writeFile("linearSweep.wav");
    buf2.writeFile("expSweep.wav");

    return 0;
}
