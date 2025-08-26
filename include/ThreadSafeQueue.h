#pragma once
#include <condition_variable>
#include <optional>
#include <queue>

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()= default;
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void push(T item)
    {
        {
            std::lock_guard lock(_mtx);
            _q.push(std::move(item));
        }
        _cv.notify_one();
    }

    std::optional<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(_mtx);
        _cv.wait(lock, [&] { return !_q.empty() || _shutdown; });
        if (_q.empty())
        {
            return std::nullopt;
        }
        T item = std::move(_q.front());
        _q.pop();
        return item;
    }

    void shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(_mtx);
            _shutdown = true;
        }
        _cv.notify_all();
    }

private:
    std::mutex _mtx;
    std::condition_variable _cv;
    std::queue<T> _q;
    bool _shutdown{false};
};
