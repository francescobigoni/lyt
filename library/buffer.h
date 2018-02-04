#pragma once
#include <vector>
#include <string>
#include <functional>

class Buffer
{
public:
    Buffer(const std::vector<float> &data, float sampleRate = 0);
    static Buffer zero(int n, float sampleRate = 0);
    float *data();
    float get(int i);
    void maps(std::function<float(int n, float value)> fn);
    void mapt(std::function<float(float t, float value)> fn);
    int numSamples();
    void set(int i, float value);
    void writeFile(std::string path);

private:
    float sampleRate;
    std::vector<float> vec;
};
