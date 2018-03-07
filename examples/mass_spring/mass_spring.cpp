#include "lyt/lyt.h"
#include <cmath>
#include <iostream>

class Mass
{
    public:
    float position;
    float velocity;
    float accel;
    float force;
    float mass;
    float dampening;
    bool isPinned = false;

    Mass(float mass, float position = 0, float dampening = 0)
    {
        this->mass = mass;
        this->position = position;
        this->dampening = dampening;
        velocity = 0;
        accel = 0;
        force = 0;
    }

    void apply(float force)
    {
        this->force += force;
    };

    void commit()
    {
        if (isPinned) return;

        force = force - dampening * velocity;
        float d = 1.0 / LYT_SETTINGS.sampleRate;
        accel = force / mass;
        velocity += d * accel;
        position += d * velocity;
        force = 0;
    };
};

class Spring
{
    public:
    float stiffness;
    float dampening;
    Mass *massA;
    Mass *massB;

    Spring(Mass *massA, Mass *massB)
    {
        this->massA = massA;
        this->massB = massB;
    }

    void solveForStiffness(float freq)
    {
        auto mass = massB->mass;
        stiffness = pow(2 * pi * freq, 2) * mass - pow(massA->dampening / (2 * mass), 2) * mass;
    }

    void calculate()
    {
        auto dist = massA->position - massB->position; 
        auto force = stiffness * dist;
        massA->apply(-force);
        massB->apply(force);
    };
};

int main(int argc, char **argv)
{
    Mass origin(0.0);
    origin.isPinned = true;

    Mass massA(0.001, 0.0, 0.001);
    Mass massB(0.0005, 0.0, 0.001);
    Mass massC(0.0001, 0.0, 0.01);
    Mass massD(0.00001, 0.0, 0.001);

    Spring springA(&origin, &massA);
    springA.solveForStiffness(440);

    Spring springB(&massA, &massB);
    springB.solveForStiffness(440);

    Spring springC(&massA, &massC);
    springC.solveForStiffness(880);

    Spring springD(&massC, &massD);
    springD.solveForStiffness(220);

    auto forceLowPass = Biquad::LowPass(1000, 1);
    massA.apply(13000);

    auto buf = Buffer::zero(samples(2));
    buf.maps([&](int n, float x)
    {
        springA.calculate();
        springB.calculate();
        springC.calculate();
        massA.commit();
        massB.commit();
        massC.commit();
        return massA.position;
    });

    buf.writeFile("output.wav");
    return 0;
}
