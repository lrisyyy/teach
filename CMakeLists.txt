cmake_minimum_required(VERSION 3.10)
project(camera_test)

find_package(OpenCV REQUIRED)

add_executable(camera_test io/example.cpp)
target_link_libraries(camera_test ${OpenCV_LIBS})
