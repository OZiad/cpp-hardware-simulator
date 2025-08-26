cmake_minimum_required(VERSION 4.0)
project(cpp_hardware_simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp-hardware-simulator
        src/main.cpp
        src/Sensor.cpp
        src/Processor.cpp
)

target_include_directories(cpp-hardware-simulator PRIVATE include)