#include "realtime.h"
#include "buffer.h"
#include "settings.h"
#include <functional>
#include <exception>
#include <portaudio.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#if __APPLE__
#include <pa_mac_core.h>
#endif

int paCallback(
    const void *inputBuffer,
    void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    Realtime *caller = (Realtime*)userData;
    auto *in = (float*)inputBuffer;
    auto *out = (float*)outputBuffer;

    if (caller->startTime < 0)
        caller->startTime = timeInfo->currentTime;

    if (caller->stopped)
    {
        memset(outputBuffer, 0, framesPerBuffer * 2);
        return 1;
    }

    if (Pa_GetStreamCpuLoad(caller->stream) > 0.9)
       std::cout << "Real-time audio consuming too much CPU time\n"; 

    float time = timeInfo->currentTime - caller->startTime;

    for (int i = 0; i < framesPerBuffer; i++)
    {
        float x = *in;
        in++;
        x += *in;
        in++;

        float y = caller->callback(caller->count, x);
        caller->count++;

        *out = y;
        out++;
        *out = y;
        out++;
    }

    return 0;
}

Realtime::Realtime()
{
    auto err = Pa_Initialize();

    if (err != paNoError )
        throw std::runtime_error(Pa_GetErrorText(err));
}

void Realtime::start(std::function<float(int n, float x)> callback)
{
    waitMutex.lock();
    this->callback = callback;

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;
    inputParameters.device = Pa_GetDefaultInputDevice();
    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = 0.005;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;   
    outputParameters.suggestedLatency = 0.005; 
    outputParameters.hostApiSpecificStreamInfo = NULL;

#if __APPLE__
    PaMacCoreStreamInfo macCoreStreamInfo;
    PaMacCore_SetupStreamInfo(&macCoreStreamInfo, paMacCoreChangeDeviceParameters);
    inputParameters.hostApiSpecificStreamInfo = &macCoreStreamInfo;
    outputParameters.hostApiSpecificStreamInfo = &macCoreStreamInfo;
#endif

    auto err = Pa_OpenStream(
        &this->stream,
        &inputParameters,
        &outputParameters,
        LYT_SETTINGS.sampleRate,
        512,
        paClipOff,
        paCallback,
        this);

    if (err != paNoError)
        throw std::runtime_error(Pa_GetErrorText(err));

    err = Pa_StartStream(stream);

    if (err != paNoError)
        throw std::runtime_error(Pa_GetErrorText(err));

    stopped = false;
    count = 0;
    startTime = -1;
}

void Realtime::stop()
{
    stopped = true;
    waitMutex.unlock();
}

void Realtime::wait()
{
    using namespace std::chrono_literals;

    while (!waitMutex.try_lock())
    {
        if (!Pa_IsStreamActive(stream))
        {
            return;
            waitMutex.unlock();
        }

        std::this_thread::sleep_for(0.01s);
    }

    waitMutex.unlock();
    Pa_CloseStream(stream);
}

