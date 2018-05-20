#include "lyt/lyt.h"
#include <cmath>
#include <iostream>

int main(int argc, char **argv)
{
    auto buf = Buffer::zero(44100 * 5);
    auto len = 1.0 / 440.0 * LYT_SETTINGS.sampleRate;
	FDelay del(len + 10, len);

	float a = 0.2;
    float y_prev = 0;
    del.write(1);

	buf.maps([&](int n, float v)
    {
        float y = a * y_prev + (1.0 - a) * del.read();
        y_prev = y;

        del.write(y);
        return y;
    });

    buf.writeFile("output.wav");


	return 0;
}