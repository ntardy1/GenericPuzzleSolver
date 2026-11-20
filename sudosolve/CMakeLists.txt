# Define include directory
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Define source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
# Glob source files
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
# Add library
add_library(sudosolve ${SOURCES})
target_include_directories(sudosolve PUBLIC
                           ${INCLUDE_DIR})

# Method to copy input files?
# https://stackoverflow.com/questions/13429656/how-to-copy-contents-of-a-directory-into-build-directory-after-make-with-cmake