#pragma once
#include "ThreadSafeQueue.hpp"


class Sensor
{
public:
    explicit Sensor(ThreadSafeQueue<int>& outQue, int hz = 10);
    ~Sensor();
    void start();
    void stop();

private:
    void run();
    ThreadSafeQueue<int>& _out;
    int _periodMs;
    std::atomic<bool> _running{false};
    std::thread _worker;
};
