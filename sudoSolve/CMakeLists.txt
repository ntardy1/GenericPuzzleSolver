cmake_minimum_required(VERSION 3.10) # minimum version of CMake required
project(sudoSolve VERSION 1.0) # project name and version
set(CMAKE_CXX_STANDARD 20) # specify a C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True) # require cmake to use the above C++ standard

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include") # define include directory
configure_file("${INCLUDE_DIR}/sudoSolveConfig.h.in" sudoSolveConfig.h)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source") # define source directory
file(GLOB sudoSolve_SOURCES "${SOURCE_DIR}/*.cpp") # define source files for sudoSolve target

add_executable(sudoSolve ${sudoSolve_SOURCES})
add_subdirectory(source)
target_link_libraries(sudoSolve source) # link the source directory to the executable
target_include_directories(sudoSolve PUBLIC
                           "${PROJECT_BINARY_DIR}") # include directories
                        #    "${PROJECT_SOURCE_DIR}/include") # include directories