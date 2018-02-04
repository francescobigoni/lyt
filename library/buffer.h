#pragma once
#include <vector>
#include <string>
#include <functional>

/**
    The \a Buffer class represents a block a audio data and contain
    common functions for manipulating that data.
*/
class Buffer
{
public:
    /** Creates a buffer containing the given data.

        @param n            The length of the buffer.
        @param sampleRate   The sampleRate of the buffer.
    */
    Buffer(const std::vector<float> &data, float sampleRate = 0);

    /** Creates a buffer of \p n zero-valued sampels.

        @param n            The length of the buffer.
        @param sampleRate   The sampleRate of the buffer.
    */
    static Buffer zero(int n, float sampleRate = 0);

    /** Gets the raw pointer to the audio data array.
    */
    float *data();

    /** Gets the `i`'th sample of the buffer.
    */
    float get(int i);

    /** Maps a function of sample number and sample value over
        this buffer. The function should look like
            
            float myMapFunc(int sampleNo, float sampleValue)

        The `maps` function is then invoked with `buf.maps(myMapFunc)`.
        You can use lambda (anonymous) functions to define the mapping
        inline.

        @param  fn          The function to map.
    */
    void maps(std::function<float(int n, float value)> fn);

    /** Maps a function of sample time and sample value over
        this buffer. The function should look like
            
            float myMapFunc(float sampleTime, float sampleValue)

        The `maps` function is then invoked with `buf.maps(myMapFunc)`.
        You can use lambda (anonymous) functions to define the mapping
        inline.

        @param  fn          The function to map.
    */
    void mapt(std::function<float(float t, float value)> fn);

    /** Returns the number of samples in this buffer.
    */
    int numSamples();

    /** Sets sample number `i` to the given `value`.  
        
        @param  i           The sample index.
        @param  value       The value.
    */
    void set(int i, float value);

    /** Writes this buffer to the disk as a `.wav` file. Throws
        `std::runtime_error` if writing fails. 
    
        @param  path        Where to store the file.      
    */
    void writeFile(std::string path);

private:
    float sampleRate;
    std::vector<float> vec;
};
