#include "TaskQueue.hpp"
#include <iostream>  // if you still want logging inside these methods

TaskQueue::TaskQueue(std::size_t maxSize) : maxSize_(maxSize) {}

void TaskQueue::push(Task task) {
    std::unique_lock<std::mutex> lock(mutex_);
    notFull_.wait(lock, [this]() { return queue_.size() < maxSize_; });
    queue_.push(std::move(task));
    notEmpty_.notify_one();
}

Task TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    notEmpty_.wait(lock, [this]() { return !queue_.empty(); });
    Task t = queue_.top();
    queue_.pop();
    notFull_.notify_one();
    return t;
}

bool TaskQueue::empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

std::size_t TaskQueue::size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

void TaskQueue::ageAll() {
    std::unique_lock<std::mutex> lock(mutex_);
    std::vector<Task> tmp;
    while (!queue_.empty()) {
        Task t = queue_.top();
        queue_.pop();
        t.age();
        tmp.push_back(std::move(t));
    }
    for (auto& t : tmp) queue_.push(std::move(t));
}

void TaskQueue::notifyAll() {
    notEmpty_.notify_all();
    notFull_.notify_all();
}
