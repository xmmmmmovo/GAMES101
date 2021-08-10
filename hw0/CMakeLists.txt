cmake_minimum_required (VERSION 3.8.11)
project (Transformation)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 REQUIRED)
include_directories("/opt/homebrew/include")

add_executable (Transformation main.cpp)