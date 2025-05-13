#include "TaskQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iostream>

int main() {
    const int numProducers = 2;
    const int numConsumers = 3;
    const int maxQueueSize = 10;
    const int maxPriority = 5;
    const auto runDuration = std::chrono::seconds(20);  // run for 20s

    TaskQueue queue(maxQueueSize);
    int globalTaskId = 0;
    std::mutex idMutex;
    std::atomic<bool> running{true};

    std::vector<std::thread> threads;

    // Start producer threads
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

    // Start consumer threads
    for (int i = 0; i < numConsumers; ++i) {
        threads.emplace_back(
            consumerThread,
            std::ref(queue),
            i,
            std::ref(running)
        );
    }

    // Monitor thread: ages every task once per second
    std::thread monitor([&]() {
        while (running.load()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.ageAll();
            std::cout << "[Monitor] aged all tasks\n";
        }
    });

    // Let the simulation run...
    std::this_thread::sleep_for(runDuration);

    // Begin shutdown
    running.store(false);
    queue.notifyAll();   // wake any waiting push/pop

    // Join all threads
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
    if (monitor.joinable()) {
        monitor.join();
    }

    std::cout << "Simulation ended cleanly.\n";
    return 0;
}
