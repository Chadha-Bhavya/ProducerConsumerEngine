#pragma once
#include <chrono>
#include <string>

class Task {
public:
    Task(int id, int priority);

    int getId() const;
    int getPriority() const;
    std::chrono::steady_clock::time_point getCreationTime() const;
    void age(); // Increases priority to prevent starvation

private:
    int id_;
    int priority_;
    std::chrono::steady_clock::time_point creationTime_;
};
