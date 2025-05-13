#pragma once
#include "Task.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>

class TaskQueue {
public:
    TaskQueue(size_t maxSize);
    
    void push(Task task);
    Task pop();
    bool empty();
    size_t size();

private:
    struct Compare {
        bool operator()(const Task& a, const Task& b) {
            return a.getPriority() < b.getPriority(); // max heap
        }
    };

    std::priority_queue<Task, std::vector<Task>, Compare> queue_;
    std::mutex mutex_;
    std::condition_variable notFull_, notEmpty_;
    size_t maxSize_;
};
