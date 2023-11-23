#include "aggregator.h"

MicrophoneDataObserver::MicrophoneDataObserver() : RawDataObserver("microphone_data")
{
  // Open the default capture device and store the handle
  snd_pcm_t *capture_handle;
  int error = snd_pcm_open(&capture_handle, "hw:0,0", SND_PCM_STREAM_CAPTURE, 0);
  if (error < 0)
  {
    std::cout << "Error opening capture device: " << snd_strerror(error) << std::endl;
    return;
  }

  // Set the capture parameters
  error = snd_pcm_set_params(capture_handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 0);
  if (error < 0)
  {
    std::cout << "Error setting capture parameters: " << snd_strerror(error) << std::endl;
    snd_pcm_close(capture_handle);
    return;
  }

  // Store the capture handle as a class variable
  this->capture_handle_ = std::make_unique<snd_pcm_t>(capture_handle);

  // This should be kept in the .cfg file
  capture_frequency_ = 44100; 
  capture_interval_seconds_ = 10;

  this->file_.CreateDataSave("");
}

void MicrophoneDataObserver::CollectData()
{
  // Start recording
  int error = snd_pcm_start(capture_handle_.get());
  if (error < 0)
  {
    std::cout << "Error starting capture: " << snd_strerror(error) << std::endl;
    return;
  }

  int frames_read;
  while (frames_read % capture_frequency_ != 0)
  {
    // Record captureInterval seconds of audio per run
    int frames = capture_frequency_ * capture_interval_seconds_;
    int buffer_size = capture_frequency_ * capture_interval_seconds_ * 2;
    char *buffer = new char[buffer_size];

    frames_read = snd_pcm_readi(capture_handle_.get(), buffer, frames);
    if (frames_read < 0)
    {
      std::cerr << "Error reading data: " << snd_strerror(frames_read) << std::endl;
      break;
    }
    this->file_.UpdateDataSave(buffer);
    delete[] buffer;
  }
}
