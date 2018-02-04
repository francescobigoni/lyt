#include "processor.h"
#include "buffer.h"
#include <exception>

void Processor::process(Buffer *input, Buffer *output)
{
    if (output == nullptr)
        output = input;

    if (input->numSamples() != output->numSamples())
        throw std::runtime_error("Processor: input and output buffers are not the same size");

    for (int i = 0; i < input->numSamples(); i++)
    {
        float v = process(input->get(i));
        output->set(i, v);
    }
}

float Processor::read()
{
    return nextOutput;
}

void Processor::write(float value)
{
    nextOutput = process(value);
}
