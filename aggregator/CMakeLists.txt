add_library(aggregator
    aggregator.h
    microphone_observer.cc
    screen_observer.cc
    website_observer.cc
)

find_package(PortAudio REQUIRED)
target_link_libraries(aggregator PRIVATE ${PortAudio_LIBRARIES})
target_include_directories(aggregator PRIVATE ${PortAudio_INCLUDE_DIRS})

