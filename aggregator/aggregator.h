#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <memory>
#include <iostream>

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
  virtual ~RawDataObserver() = default;
  virtual void CollectData() = 0;

protected:
  RawAggregatorFile file_;
};

class ScreenDataObserver : public RawDataObserver
{
public:
  ScreenDataObserver() : RawDataObserver("screen_data") {}
  ~ScreenDataObserver() override;
  void CollectData() override;

private:
  std::unique_ptr<Display, decltype(&XCloseDisplay)> display_{XOpenDisplay(nullptr), XCloseDisplay};
  Window root_{DefaultRootWindow(display_.get())};
  XWindowAttributes window_attributes_;
};

class MicrophoneDataObserver : public RawDataObserver
{
public:
  MicrophoneDataObserver() : RawDataObserver("screen_data") {}
  ~MicrophoneDataObserver() override;
  void CollectData() override;

private:

};

#endif // AGGREGATOR_H