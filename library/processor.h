#pragma once
#include "buffer.h"

/**
    The `Processor` class is a base class for objects that can process
    audio.
*/
class Processor
{
    public:
    /** The functions that does the main processing. Samples are read
        from `input`, processed and written to output. The `input` and
        `output` buffers may be the same.
        
        If the `output` buffer pointer is set to `nullptr`, the `input`
        buffer will be used for output.

        @param  input       The buffer to read samples from.
        @param  output      The buffer to write processed samples to.
    */
    void process(Buffer *input, Buffer *output = nullptr);

    /** Process one input value and returns the result. This function
        should be inplemented by inheritors of `Processor` as the main
        audio processing function.

        @param  value       The sample to process.
    */
    virtual float process(float value) = 0;

    /** Returns the next output sample from the processor. `write` should
        be called before output can be read again.
    */
    float read();

    /** Writes an input sample for the processor to process. The output
        can be read using `read`.

        @param  value       The next input sample.
    */
    void write(float value);

    private:
    float nextOutput = 0;
};
