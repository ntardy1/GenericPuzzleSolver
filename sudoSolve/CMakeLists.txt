cmake_minimum_required(VERSION 3.10) # minimum version of CMake required
project(sudoSolve VERSION 1.0) # project name and version
set(CMAKE_CXX_STANDARD 20) # specify a C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True) # require cmake to use the above C++ standard
configure_file(sudoSolveConfig.h.in sudoSolveConfig.h)

add_executable(sudoSolve sudoSolve.cpp)
target_include_directories(sudoSolve PUBLIC
                           ${PROJECT_BINARY_DIR}) # include directories