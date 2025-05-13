#include "TaskQueue.hpp"
#include <iostream>

TaskQueue::TaskQueue(size_t maxSize) : maxSize_(maxSize) {}

void TaskQueue::push(Task task) {
    std::unique_lock<std::mutex> lock(mutex_);
    notFull_.wait(lock, [this]() { return queue_.size() < maxSize_; });

    queue_.push(task);
    std::cout << "[Push] Task ID: " << task.getId() << " | Priority: " << task.getPriority() << "\n";
    notEmpty_.notify_one();
}

Task TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    notEmpty_.wait(lock, [this]() { return !queue_.empty(); });

    Task top = queue_.top();
    queue_.pop();
    std::cout << "[Pop] Task ID: " << top.getId() << " | Priority: " << top.getPriority() << "\n";
    notFull_.notify_one();
    return top;
}

bool TaskQueue::empty() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

size_t TaskQueue::size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}
