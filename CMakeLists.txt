# ============================ PROJECT INFORMATION =============================
# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)
# Project name and version
project(sudoSolve VERSION 1.0)
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
# ==============================================================================

# ===================== EXTERNAL DEPENDENCY CONFIGURATION ======================
find_package(Boost REQUIRED COMPONENTS program_options)
# ==============================================================================

# ====================== LOCAL DEPENDENCY CONFIGURATION ========================
# Define include directory
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Copy configuration header file
configure_file("${INCLUDE_DIR}/sudoSolveConfig.h.in" sudoSolveConfig.h)
# Define source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
# Define source files for sudoSolve target
file(GLOB sudoSolve_SOURCES "${SOURCE_DIR}/*.cpp")
# ==============================================================================

# ========================= EXECUTABLE CONFIGURATION ===========================
# Define the executable with the top-level source files
add_executable(sudoSolve ${sudoSolve_SOURCES})
# Ensure the source library (i.e., the files in the source directory) get built
add_subdirectory(source)
# Link the executable against required libraries
target_link_libraries(sudoSolve PRIVATE
                      source # link the source directory to the executable
                      Boost::program_options) # link Boost::program_options to the executable
# Include directories
target_include_directories(sudoSolve PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/include")
# ==============================================================================