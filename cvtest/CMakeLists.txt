cmake_minimum_required(VERSION 3.1.3)
project(cvtest VERSION 0.1.0)
find_package(OpenCV REQUIRED)
include_directories({%OPENCV_DIR%\lib})
add_executable(cvtest main.cpp)
target_link_libraries(opencv {%OPENCV_DIR%\lib})