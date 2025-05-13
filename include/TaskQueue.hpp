#pragma once

#include "Task.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstddef>  // for std::size_t

class TaskQueue {
public:
    explicit TaskQueue(std::size_t maxSize);

    void push(Task task);
    Task pop();
    bool empty() const;
    std::size_t size() const;

    // Aging & shutdown support
    void ageAll();
    void notifyAll();

private:
    struct Compare {
        bool operator()(const Task& a, const Task& b) const {
            return a.getEffectivePriority() < b.getEffectivePriority();
        }
    };

    std::priority_queue<Task, std::vector<Task>, Compare> queue_;
    mutable std::mutex mutex_;
    std::condition_variable notFull_, notEmpty_;
    std::size_t maxSize_;
};
