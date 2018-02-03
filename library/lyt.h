#pragma once
#include <vector>
#include <string>

class Buffer
{
public:
    Buffer(const std::vector<float> &data);

    float get(int i);
    void set(int i, float value);
    void writeFile(std::string path);

private:
    float sampleRate;
    std::vector<float> vec;
};
