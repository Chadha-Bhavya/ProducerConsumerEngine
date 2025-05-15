#pragma once
#include <cstddef>
#include <atomic>   

extern std::atomic<bool> affinityEnabled;

void bindThreadToCore(std::size_t core);