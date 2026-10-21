find_package(OpenCV REQUIRED)
add_executable(task1 explain.cpp)
target_link_libraries(task1 ${OpenCV_LIBS})
