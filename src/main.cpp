#include <chrono>
#include <iostream>
#include <thread>
#include "Processor.hpp"
#include "Sensor.hpp"
#include "ThreadSafeQueue.hpp"
int main()
{
    ThreadSafeQueue<int> q;

    Sensor sensor(q, /*hz=*/10);
    Processor processor(q, "data_log.txt");

    sensor.start();
    processor.start();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    sensor.stop();
    q.shutdown();
    processor.stop();

    std::cout << "Done. Check data_log.txt\n";
    return 0;
}
