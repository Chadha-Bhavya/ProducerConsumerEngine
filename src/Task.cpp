#include "Task.hpp"

Task::Task(int id, int priority)
    : id_(id), priority_(priority), creationTime_(std::chrono::steady_clock::now()) {}

int Task::getId() const { return id_; }
int Task::getPriority() const { return priority_; }

std::chrono::steady_clock::time_point Task::getCreationTime() const {
    return creationTime_;
}

void Task::age() {
    priority_++; // Simple aging mechanism
}

int Task::getEffectivePriority() const {
    using ms = std::chrono::milliseconds;
    auto age = std::chrono::duration_cast<ms>(
        std::chrono::steady_clock::now() - creationTime_
    ).count();
    // e.g., every 1000ms adds +1 priority
    return priority_ + static_cast<int>(age / 1000);
}
