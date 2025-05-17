#include "TaskQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "Logger.hpp"
#include "Affinity.hpp"

#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iostream>

void printUsage(const char* prog) {
    std::cout << "Usage: " << prog << " [-p producers] [-c consumers] [-q queue_size] "
              << "[-r run_seconds] [-m max_priority] [-A] [-h]\n"
              << "  -A  enable thread affinity\n";
}

int main(int argc, char* argv[]) {
    int numProducers = 2, numConsumers = 3, maxQueueSize = 10;
    int maxPriority = 5, runSeconds = 20;

    int opt;
    while ((opt = getopt(argc, argv, "p:c:q:r:m:Ah")) != -1) {
        switch (opt) {
            case 'p': numProducers = std::atoi(optarg); break;
            case 'c': numConsumers = std::atoi(optarg); break;
            case 'q': maxQueueSize = std::atoi(optarg); break;
            case 'r': runSeconds   = std::atoi(optarg); break;
            case 'm': maxPriority  = std::atoi(optarg); break;
            case 'A': affinityEnabled.store(true); break;
            case 'h':
            default: printUsage(argv[0]); return opt=='h'?0:1;
        }
    }

    Logger::log("[Config] p=" + std::to_string(numProducers)
                + " c=" + std::to_string(numConsumers)
                + " q=" + std::to_string(maxQueueSize)
                + " r=" + std::to_string(runSeconds)
                + " m=" + std::to_string(maxPriority)
                + (affinityEnabled ? " Affinity ON" : ""));

    TaskQueue queue(maxQueueSize);
    int globalId = 0;
    std::mutex idMutex;
    std::atomic<bool> running{true};
    std::vector<std::thread> threads;

    // Producers
    for (int i = 0; i < numProducers; ++i)
        threads.emplace_back(
            producerThread,
            std::ref(queue), i,
            std::ref(globalId),
            std::ref(idMutex),
            maxPriority,
            std::ref(running)
        );

    // Consumers
    for (int i = 0; i < numConsumers; ++i)
        threads.emplace_back(
            consumerThread,
            std::ref(queue), i,
            std::ref(running)
        );

    // Monitor
    std::thread monitor([&]() {
        while (running.load()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.ageAll();
            Logger::log("[Monitor] Aged all tasks");
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(runSeconds));
    running.store(false);
    queue.notifyAll();

    for (auto& t : threads) if (t.joinable()) t.join();
    if (monitor.joinable()) monitor.join();

    Logger::log("Simulation ended cleanly.");
    return 0;
}
