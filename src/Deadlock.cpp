#include "Deadlock.hpp"
#include "Logger.hpp"
#include <thread>
#include <chrono>
#include <mutex>

static std::mutex mtxA;
static std::mutex mtxB;

void worker1(std::atomic<bool>& running) {
    if (!running.load()) return;
    Logger::log("[Deadlock] Worker1 bound to deadlock path");
    std::lock_guard<std::mutex> lockA(mtxA);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Logger::log("[Deadlock] Worker1 attempting lock B");
    std::lock_guard<std::mutex> lockB(mtxB);
    Logger::log("[Deadlock] Worker1 acquired both locks");
}

void worker2(std::atomic<bool>& running) {
    if (!running.load()) return;
    Logger::log("[Deadlock] Worker2 bound to deadlock path");
    std::lock_guard<std::mutex> lockB(mtxB);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Logger::log("[Deadlock] Worker2 attempting lock A");
    std::lock_guard<std::mutex> lockA(mtxA);
    Logger::log("[Deadlock] Worker2 acquired both locks");
}

void startDeadlockDemo(std::atomic<bool>& running) {
    std::thread t1(worker1, std::ref(running));
    std::thread t2(worker2, std::ref(running));
    // Detector thread
    std::thread detector([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        Logger::log("[Deadlock] Deadlock detected! Initiating recovery.");
        running.store(false);
    });

    t1.detach(); t2.detach(); detector.detach();
}