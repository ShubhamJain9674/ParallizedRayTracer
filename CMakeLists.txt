cmake_minimum_required(VERSION 3.16)

project(ParallizedRayTracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RayTracer
    src/main.cpp
)
target_include_directories(RayTracer PRIVATE include)

# OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(RayTracer PRIVATE OpenMP::OpenMP_CXX)

# Optimization toggle
option(USE_HIGH_OPT "Enable aggressive optimization" ON)

if(USE_HIGH_OPT)
    target_compile_options(RayTracer PRIVATE -O3)
else()
    target_compile_options(RayTracer PRIVATE -O1)
endif()

# Compiler-specific tuning
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(RayTracer PRIVATE -march=native)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(RayTracer PRIVATE -xHost)
endif()