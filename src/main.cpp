#include "TaskQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "Logger.hpp"

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>

int main() {
    const int numProducers   = 2;
    const int numConsumers   = 3;
    const int maxQueueSize   = 10;
    const int maxPriority    = 5;
    const auto runDuration   = std::chrono::seconds(20);

    TaskQueue queue(maxQueueSize);
    int globalTaskId = 0;
    std::mutex idMutex;
    std::atomic<bool> running{true};
    std::vector<std::thread> threads;

    // Producers
    for (int i = 0; i < numProducers; ++i) {
        threads.emplace_back(
            producerThread,
            std::ref(queue),
            i,
            std::ref(globalTaskId),
            std::ref(idMutex),
            maxPriority,
            std::ref(running)
        );
    }

    // Consumers
    for (int i = 0; i < numConsumers; ++i) {
        threads.emplace_back(
            consumerThread,
            std::ref(queue),
            i,
            std::ref(running)
        );
    }

    // Monitor thread
    std::thread monitor([&]() {
        while (running.load()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.ageAll();
            Logger::log("[Monitor] Aged all tasks");
        }
    });

    // Run, then signal shutdown
    std::this_thread::sleep_for(runDuration);
    running.store(false);
    queue.notifyAll();

    // Join
    for (auto &t : threads) if (t.joinable()) t.join();
    if (monitor.joinable()) monitor.join();

    Logger::log("Simulation ended cleanly.");
    return 0;
}
