cmake_minimum_required(VERSION 3.10)
project(ColorCorrect)

find_package(OpenCV REQUIRED)

add_executable(color_correct example.cpp)
target_link_libraries(color_correct ${OpenCV_LIBS})
