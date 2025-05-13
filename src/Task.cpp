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
