cmake_minimum_required(VERSION 3.10)
project(screenwhisper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

# ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# screenwhisper executable target
add_executable(screenwhisper main.cc)
target_link_libraries(screenwhisper ${CURSES_LIBRARIES})

install(TARGETS screenwhisper DESTINATION bin)