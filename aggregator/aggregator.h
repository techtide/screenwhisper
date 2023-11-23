#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <string>

// Container file that allows for generic data to be saved
class RawAggregatorFile {
public:
    RawAggregatorFile(const std::string& file_path);

    // Updates the existing file object contents with the new data
    template <typename T>
    void updateDataSave(const T& data);

    // Save a file of generic type to the specific path 
    template <typename T>
    void createDataSave(const T& data);
private:
    std::string file_path_;
};

// Abstract class to observe raw data from various sources
class RawDataObserver {
public:
    RawDataObserver(const std::string& file_path);
    virtual ~RawDataObserver() = default;
    virtual void collectData(const RawAggregatorFile& agg) = 0;
private:
    RawAggregatorFile file_;
};

class ScreenDataObserver : public RawDataObserver {
public:
    explicit ScreenDataObserver() = default;
    virtual ~ScreenDataObserver() override;
    virtual void collectData(const RawAggregatorFile& agg) override;
private:
    const RawAggregatorFile file_;
};

class MicrophoneDataObserver : public RawDataObserver {
public:
    explicit MicrophoneDataObserver() = default;
    virtual ~MicrophoneDataObserver() override;
    virtual void collectData(const RawAggregatorFile& agg) override;
private:
    const RawAggregatorFile file_;
};

class WebDataObserver : public RawDataObserver {
public:
    explicit WebDataObserver() = default;
    virtual ~WebDataObserver() override;
    virtual void collectData(const RawAggregatorFile& agg) override;
private:
    const RawAggregatorFile file_;
};

#endif // AGGREGATOR_H