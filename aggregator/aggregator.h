#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <memory>
#include <iostream>
#include <alsa/asoundlib.h>

// Container file that allows for generic data to be saved
class RawAggregatorFile
{
public:
  RawAggregatorFile() : file_path_("temp_file") {}

  // Constructor that takes in a file path
  RawAggregatorFile(const std::string &file_path) : file_path_(file_path) {}

  // Updates the existing file object contents with the new data
  template <typename T>
  void UpdateDataSave(const T &data);

  // Save a file of generic type to the specific path
  template <typename T>
  void CreateDataSave(const T &data);

private:
  std::string file_path_;
};

// Abstract class to observe raw data from various sources
class RawDataObserver
{
public:
  RawDataObserver(const std::string &file_path) : file_(file_path) {}
  virtual void CollectData() = 0;

protected:
  RawAggregatorFile file_;
};

// Collect raw screencaps of the display from the root window in X11
class ScreenDataObserver : public RawDataObserver
{
public:
  ScreenDataObserver() : RawDataObserver("screen_data") {}
  void CollectData() override;

private:
  std::unique_ptr<Display, decltype(&XCloseDisplay)> display_{XOpenDisplay(nullptr), XCloseDisplay};
  Window root_{DefaultRootWindow(display_.get())};
  XWindowAttributes window_attributes_;
  ~ScreenDataObserver() {
    XCloseDisplay(display_.get());
  }
};

// Collect the raw microphone audio data in the background
class MicrophoneDataObserver : public RawDataObserver
{
public:
  MicrophoneDataObserver() : RawDataObserver("screen_data") {}
  void CollectData() override;

private:
  std::unique_ptr<snd_pcm_t> capture_handle_;
  int capture_frequency_;
  ~MicrophoneDataObserver() {
    snd_pcm_close(capture_handle_.get());
  }
};

#endif // AGGREGATOR_H