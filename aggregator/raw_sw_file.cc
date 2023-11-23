#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class RawAggregatorFile {
public:
    RawAggregatorFile(const std::string& file_path) : file_path_(file_path) {}

    // Updates the existing file object contents with the new data
    void updateDataSave(const T& data) {
        std::ofstream file(file_path_, std::ios::binary | std::ios::trunc);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&data), sizeof(data));
            file.close();
        } else {
            std::cerr << "Error: Unable to open file for update." << std::endl;
        }
    }

    // Save a file of generic type to the specific path 
    void createDataSave(const T& data) {
        std::ofstream file(file_path_, std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&data), sizeof(data));
            file.close();
        } else {
            std::cerr << "Error: Unable to create file for saving." << std::endl;
        }
    }

private:
    std::string file_path_;
};
