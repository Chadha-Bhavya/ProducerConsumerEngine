#include "Producer.hpp"
#include "Task.hpp"
#include "TaskQueue.hpp"
#include "Logger.hpp"

#include <chrono>
#include <thread>
#include <random>

void producerThread(TaskQueue& queue,
                    int producerId,
                    int& globalTaskId,
                    std::mutex& idMutex,
                    int maxPriority,
                    std::atomic<bool>& running) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleepDist(100, 300);
    std::uniform_int_distribution<> prioDist(1, maxPriority);

    while (running.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepDist(gen)));

        int taskId;
        {
            std::lock_guard<std::mutex> lock(idMutex);
            taskId = globalTaskId++;
        }

        Task task(taskId, prioDist(gen));
        queue.push(std::move(task));
        Logger::log(
            "[Producer " + std::to_string(producerId) +
            "] Created Task " + std::to_string(taskId) +
            " (prio=" + std::to_string(task.getPriority()) + ")"
        );
    }
}
