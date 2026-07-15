cmake_minimum_required(VERSION 3.15)
project(CudaRayTracing CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} src/main.cpp src/scenes.cpp src/benchmark.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
