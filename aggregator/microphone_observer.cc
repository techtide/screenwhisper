#include <iostream>
#include <memory>
#include "portaudio.h"

class AudioStream {
public:
    AudioStream() : stream(nullptr) {}

    bool initialize() {
        return Pa_Initialize() == paNoError;
    }

    bool openStream() {
        return Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, this) == paNoError;
    }

    bool startStream() {
        return Pa_StartStream(stream) == paNoError;
    }

    bool stopStream() {
        return Pa_StopStream(stream) == paNoError;
    }

    bool closeStream() {
        return Pa_CloseStream(stream) == paNoError;
    }

    ~AudioStream() {
        if (stream) {
            Pa_Terminate();
        }
    }

private:
    static int audioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
        // Process the microphone input data here
        const float* in = static_cast<const float*>(inputBuffer);
        for (unsigned int i = 0; i < framesPerBuffer; ++i) {
            std::cout << in[i] << " ";
        }
        std::cout << std::endl;

        return paContinue;
    }

    PaStream* stream;
};

int main() {
    AudioStream audioStream;

    if (!audioStream.initialize() || !audioStream.openStream() || !audioStream.startStream()) {
        std::cerr << "Failed to initialize and start audio stream." << std::endl;
        return 1;
    }

    std::cout << "Press Enter to stop recording..." << std::endl;
    std::cin.ignore();

    if (!audioStream.stopStream() || !audioStream.closeStream()) {
        std::cerr << "Failed to stop and close audio stream." << std::endl;
        return 1;
    }

    return 0;
}

