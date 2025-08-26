#include "Sensor.hpp"

#include <random>

Sensor::Sensor(ThreadSafeQueue<int>& outQue, const int hz) : _out(outQue), _periodMs(hz > 0 ? (1000 / hz) : 100) {}
Sensor::~Sensor() { stop(); }

void Sensor::start()
{
    if (_running.exchange(true))
    {
        return;
    }
    _worker = std::thread(&Sensor::run, this);
}

void Sensor::stop()
{
    if (!_running.exchange(false))
    {
        return;
    }
    if (_worker.joinable())
    {
        _worker.join();
    }
}

void Sensor::run()
{
    // Generate a bunch of random numbers between 0 and 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);

    while (_running.load())
    {
        _out.push(dist(gen));
        std::this_thread::sleep_for(std::chrono::milliseconds(_periodMs));
    }
}
