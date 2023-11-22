cmake_minimum_required(VERSION 3.10)
project(screenwhisper)

# Include submodules which are all called by the driver, main.cc
add_subdirectory(aggregator)
add_subdirectory(inference)
add_subdirectory(knowledge)

# Main executable
add_executable(main main.cc)

# Link against submodules
target_link_libraries(main
    PRIVATE aggregator
    PRIVATE inference
    PRIVATE knowledge
)
