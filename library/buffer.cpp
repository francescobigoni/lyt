#include <sndfile.h>
#include <vector>
#include <string>
#include <functional>
#include <exception>
#include "buffer.h"

Buffer::Buffer(const std::vector<float> &data, float sampleRate)
{
    vec = data;
    this->sampleRate = sampleRate;
}

Buffer Buffer::zero(int n, float sampleRate)
{
    std::vector<float> vec(n, 0);
    return Buffer::Buffer(vec, sampleRate);
}

float *Buffer::data()
{
    return vec.data();
}

float Buffer::get(int i)
{
   return vec[i]; 
}

void Buffer::maps(std::function<float(int n, float value)> fn)
{
    for (int i = 0; i < numSamples(); i++)
    {
        float v = fn(i, get(i));
        set(i, v);
    }
}

void Buffer::mapt(std::function<float(float t, float value)> fn)
{
    for (int i = 0; i < numSamples(); i++)
    {
        float t = (float)i / sampleRate;
        float v = fn(t, get(i));
        set(i, v);
    }
}

int Buffer::numSamples()
{
    return vec.size();
}

void Buffer::set(int i, float value)
{
    vec[i] = value;
}

void Buffer::writeFile(std::string path)
{
    SF_INFO info;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.samplerate = 44100;
    info.channels = 1;
 
    SNDFILE *file = sf_open(path.c_str(), SFM_WRITE, &info);
    
    if (file == NULL)
    {
        std::string err(sf_strerror(file));
        throw std::runtime_error("Could not open file " + path + "for writing because: " + err);
    }

    int numWritten = sf_write_float(file, data(), numSamples());

    if (numWritten != numSamples())
    {
        throw std::runtime_error("Did not write the expected number of samples");
    }

    sf_close(file);
}