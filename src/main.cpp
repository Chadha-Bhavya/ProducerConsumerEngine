#include "TaskQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "Logger.hpp"

#include <unistd.h>      // for getopt
#include <cstdlib>       // for std::atoi
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>

void printUsage(const char* prog) {
    std::cout << "Usage: " << prog << " [-p producers] [-c consumers] "
              << "[-q queue_size] [-r run_seconds] [-m max_priority]\n"
              << "Defaults: p=2, c=3, q=10, r=20, m=5\n";
}

int main(int argc, char* argv[]) {
    // Default parameters
    int numProducers = 2;
    int numConsumers = 3;
    int maxQueueSize = 10;
    int maxPriority  = 5;
    int runSeconds   = 20;

    // Parse CLI flags
    int opt;
    while ((opt = getopt(argc, argv, "p:c:q:r:m:h")) != -1) {
        switch (opt) {
            case 'p': numProducers = std::atoi(optarg); break;
            case 'c': numConsumers = std::atoi(optarg); break;
            case 'q': maxQueueSize = std::atoi(optarg); break;
            case 'r': runSeconds   = std::atoi(optarg); break;
            case 'm': maxPriority  = std::atoi(optarg); break;
            case 'h':
            default:
                printUsage(argv[0]);
                return opt == 'h' ? 0 : 1;
        }
    }

    Logger::log("[Config] Producers=" + std::to_string(numProducers) +
                " Consumers=" + std::to_string(numConsumers) +
                " QueueSize=" + std::to_string(maxQueueSize) +
                " Run=" + std::to_string(runSeconds) + "s" +
                " MaxPrio=" + std::to_string(maxPriority));

    TaskQueue queue(maxQueueSize);
    int globalTaskId = 0;
    std::mutex idMutex;
    std::atomic<bool> running{true};

    std::vector<std::thread> threads;

    // Start producers
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

    // Start consumers
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

    // Run for specified duration
    std::this_thread::sleep_for(std::chrono::seconds(runSeconds));

    // Shutdown
    running.store(false);
    queue.notifyAll();

    for (auto &t : threads) if (t.joinable()) t.join();
    if (monitor.joinable()) monitor.join();

    Logger::log("Simulation ended cleanly.");
    return 0;
}
