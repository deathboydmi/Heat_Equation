cmake_minimum_required(VERSION 3.1)

project(Heat_Equation)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)

add_library(tofunction STATIC ./source/tofunction/tofunction.cpp)

add_executable(he_exe ./source/main.cpp)

target_link_libraries(he_exe tofunction)