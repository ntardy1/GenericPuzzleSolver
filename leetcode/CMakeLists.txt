# Define include directory
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# Define source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
# Glob source files
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
# Add library
add_library(leetcode ${SOURCES})
target_include_directories(leetcode PUBLIC
                           ${INCLUDE_DIR})