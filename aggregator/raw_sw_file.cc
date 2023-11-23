#include <iostream>
#include <fstream>
#include <string>
#include "aggregator.h"

// Updates the existing file object contents with the new data
template <typename T>
void RawAggregatorFile::UpdateDataSave(const T &data)
{
  std::ofstream file(file_path_, std::ios::binary | std::ios::trunc);
  if (file.is_open())
  {
    file.write(reinterpret_cast<const char *>(&data), sizeof(data));
    file.close();
  }
  else
  {
    std::cerr << "Error: Unable to open file for update." << std::endl;
  }
}

// Save a file of generic type to the specific path
template <typename T>
void RawAggregatorFile::CreateDataSave(const T &data)
{
  std::ofstream file(file_path_, std::ios::binary);
  if (file.is_open())
  {
    file.write(reinterpret_cast<const char *>(&data), sizeof(data));
    file.close();
  }
  else
  {
    std::cerr << "Error: Unable to create file for saving." << std::endl;
  }
}