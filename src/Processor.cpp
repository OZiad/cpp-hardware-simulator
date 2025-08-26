#include "Processor.hpp"

Processor::Processor(ThreadSafeQueue<int>& inQue, const std::string& logPath) : _in(inQue), _logPath(logPath) {}
Processor::~Processor() { stop(); }


void Processor::start()
{
    if (_running.exchange(true))
    {
        return;
    }
    _worker = std::thread(&Processor::run, this);
}
void Processor::stop()
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


void Processor::run()
{
    std::ofstream log(_logPath, std::ios::out);
    std::size_t count = 0;

    while (_running.load())
    {
        std::optional<int> item = _in.wait_and_pop();
        if (!item.has_value())
        {
            break;
        }

        ++count;
        const int v = *item;
        if (log.is_open())
        {
            log << "Sample #" << count << " = " << v << (v > 80 ? "  <-- threshold!!!" : "") << "\n";
        }
    }
    if (log.is_open())
    {
        log << "Processed " << count << " samples.\n";
        log.flush();
    }
}
