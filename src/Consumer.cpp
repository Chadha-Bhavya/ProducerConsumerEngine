#include "Consumer.hpp"
#include "TaskQueue.hpp"
#include "Logger.hpp"
#include "Affinity.hpp"

#include <thread>
#include <chrono>

void consumerThread(TaskQueue& queue,
                    int consumerId,
                    std::atomic<bool>& running) 
{
    if (affinityEnabled.load()) {
        bindThreadToCore(consumerId);
    }

    while (running.load() || !queue.empty()) {
        Task task = queue.pop();
        Logger::log(
            "[Consumer " + std::to_string(consumerId) +
            "] Processing Task " + std::to_string(task.getId())
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
