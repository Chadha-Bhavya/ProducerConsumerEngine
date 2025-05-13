#pragma once
#include <mutex>
#include <string>
#include <iostream>

class Logger {
public:
    static void log(const std::string &msg) {
        std::lock_guard<std::mutex> lock(mu_);
        std::cout << msg << '\n';
    }
private:
    static std::mutex mu_;
};
