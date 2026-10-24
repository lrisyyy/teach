cmake_minimum_required(VERSION 3.10)
project(io_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(io_example example.cpp)
target_link_libraries(io_example ${OpenCV_LIBS})
