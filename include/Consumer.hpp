#pragma once
#include "TaskQueue.hpp"
#include <atomic>

void consumerThread(TaskQueue& queue,
                    int consumerId,
                    std::atomic<bool>& running);
