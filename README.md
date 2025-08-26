# C++ Hardware Simulator

Minimal C++20 project simulating a hardware data pipeline.  
Implements a multithreaded producer–consumer system with a thread-safe queue, condition variables, and clean shutdown.

## Build & Run
Using g++:
```bash
g++ -std=c++20 -Iinclude src/*.cpp -o hardware_sim
./hardware_sim
