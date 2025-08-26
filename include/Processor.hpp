#pragma once
#include <fstream>
#include "ThreadSafeQueue.hpp"

class Processor
{

public:
    explicit Processor(ThreadSafeQueue<int>& inQue, const std::string& logPath = "data_log.txt");
    ~Processor();

    void start();
    void stop();

private:
    void run();
    ThreadSafeQueue<int>& _in;
    const std::string _logPath;
    std::atomic<bool> _running{false};
    std::thread _worker;
};
