#pragma once
#include "buffer.h"

/**
    The `Processor` class is a base class for objects that can process
    audio.
*/
class Processor
{
    /** The functions that does the main processing. Samples shoud be 
        read from `input`, processed and written to output. The `input`
        and `output` buffers may be the same.
        
        If the `output` buffer pointer is set to `nullptr`, the `input`
        buffer will be used for output.

        @param  input       The buffer to read samples from.
        @param  output      The buffer to write processed samples to.
    */
    void process(Buffer *input, Buffer *output = nullptr) = 0;
};
