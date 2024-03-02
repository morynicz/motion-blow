#pragma once
#include <deque>
#include <mutex>
#include <optional>

template <typename T> class Queue
{
  public:
    Queue(uint maxSize) : maxSize(maxSize){};
    void push(const T &item)
    {
        std::lock_guard<std::mutex> guard(mtx);
        buffer.push_front(item);
        if (buffer.size() > maxSize)
            buffer.pop_back();
    }
    std::optional<T> pop()
    {
        std::lock_guard<std::mutex> guard(mtx);
        if (not buffer.empty())
        {
            auto it = buffer.back();
            buffer.pop_back();
            return it;
        }
        return std::nullopt;
    }

  private:
    uint maxSize;
    std::mutex mtx{};
    std::deque<T> buffer{};
};