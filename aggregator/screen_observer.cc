#include "aggregator.h"

ScreenDataObserver::ScreenDataObserver() : RawDataObserver("screen_data")
{
  display_ = XOpenDisplay(nullptr);
  if (!display_) {
    std::cerr << "Error: Unable to open display." << std::endl;
  }
  XGetWindowAttributes(display_, root_, &window_attributes_);
  this->file_.CreateDataSave("");
}

void ScreenDataObserver::CollectData()
{
  // TODO(armanbhalla): XGetImage takes in a (width, height) tuple, but we need
  // to take these parameters interactively from the user, who defines a speci-
  // fic portion of the screen which will be captured by ScreenDataObserver.
  int width = window_attributes_.width;
  int height = window_attributes_.height;
  XImage* image = XGetImage(display_, root_, 0, 0, width, height, AllPlanes, ZPixmap);
  if (!image) {
    std::cerr << "Error: Unable to get image." << std::endl;
    return;
  }
  // TODO(armanbhalla): should this be saved as a PPM with a PPM header?
  this->file_.UpdateDataSave(image->data);
  XDestroyImage(image);
}