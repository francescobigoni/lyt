#pragma once
#include <functional>
#include <portaudio.h>
#include <condition_variable>
#include <mutex>
#include "buffer.h"


/// Enables simple real-time audio processing.
class Realtime
{
    public:
    /// Creates a new Realtime audio instance
    Realtime();

    /// Starts the realtime audio stream with the given audio processing
    /// callback.
    /// @param  callback    The audio callback
    void start(std::function<float(int n, float x)> callback);

    /// Stops the current audio stream. Causes a call to `wait` to continue.
    void stop();

    /// Waits for 
    void wait();

    std::function<float(int n, float x)> callback;
    double startTime;

    bool stopped;
    int count;
    PaStream *stream;
    std::mutex waitMutex;

friend int paCallback(
    const void *inputBuffer,
    void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData);
};
