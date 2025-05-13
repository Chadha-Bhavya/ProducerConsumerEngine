#pragma once
#include "TaskQueue.hpp"
#include <mutex>
#include <atomic>

void producerThread(TaskQueue& queue,
                    int producerId,
                    int& globalTaskId,
                    std::mutex& idMutex,
                    int maxPriority,
                    std::atomic<bool>& running);
