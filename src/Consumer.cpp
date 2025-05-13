#include "Consumer.hpp"
#include "TaskQueue.hpp"
#include <thread>
#include <chrono>
#include <iostream>

void consumerThread(TaskQueue& queue,
                    int consumerId,
                    std::atomic<bool>& running) 
{
    while (running.load() || !queue.empty()) {
        Task task = queue.pop();
        std::cout << "[Consumer " << consumerId 
                  << "] Processing Task " << task.getId() 
                  << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
