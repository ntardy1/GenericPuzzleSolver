add_library(source main.cpp) # create a library comprised of the source files
target_include_directories(source PUBLIC "${PROJECT_BINARY_DIR}") # include directories