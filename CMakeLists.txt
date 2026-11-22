############################## Project Information #############################
# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)
# Project name and version
project(GenericPuzzleSolver VERSION 0.1.0)
# Specify a C++ standard
set(CMAKE_CXX_STANDARD 17)
# Require cmake to use the above C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Specify the output location for runtime target files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Apply the final runtime search paths to the executable
# as soon as the linking completes
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
# Specify runtime search paths for target files
# $ORIGIN is the absolute path to the folder containing the executable
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")

####################### External Dependency Configuration ######################
find_package(Boost REQUIRED COMPONENTS program_options)

######################## Local Dependency Configuration ########################
# Define include directory
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Copy configuration header file
configure_file("${INCLUDE_DIR}/GenericPuzzleSolverConfig.h.in" GenericPuzzleSolverConfig.h)
# Define source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
# Define source files for GPS target
file(GLOB GPS_SOURCES "${SOURCE_DIR}/*.cpp")

########################### Executable Configuration ###########################
# Define the executable with the top-level source files
add_executable(GPS ${GPS_SOURCES})
# Add the Sudoku module to the build
add_subdirectory(sudosolve)
# Link the executable against required libraries
target_link_libraries(GPS PRIVATE
                      Boost::program_options
                      sudosolve)
# Include directories
target_include_directories(GPS PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/include")
