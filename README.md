# ProducerConsumerEngine

A terminal-based simulation of a multithreaded producer–consumer system in C++.

## Purpose

Demonstrate concurrency concepts using C++17 and standard threading tools:

- Bounded buffer with priority scheduling
- Starvation prevention via task aging
- Optional thread affinity
- Graceful shutdown and configurable parameters via CLI

## Features Implemented

1. **Core Classes**

   - `Task`: ID, priority, creation time, aging method
   - `TaskQueue`: thread-safe, bounded, uses `std::priority_queue`, `std::mutex`, `std::condition_variable`

2. **Producer & Consumer Threads**

   - Producers generate tasks at random intervals and block when the queue is full
   - Consumers process highest-priority tasks and drain remaining tasks on shutdown

3. **Aging & Starvation Prevention**

   - Effective priority increases over time
   - Monitor thread periodically calls `ageAll()`

4. **Graceful Shutdown**

   - Runs for a configurable duration
   - Signals producers to stop, allows consumers to finish remaining tasks

5. **Thread-Safe Logging**

   - `Logger`: serializes output to avoid interleaving

6. **Command-Line Interface**

   - Flags to configure:

     - `-p`: number of producers (default 2)
     - `-c`: number of consumers (default 3)
     - `-q`: queue size (default 10)
     - `-r`: run duration in seconds (default 20)
     - `-m`: max task priority (default 5)
     - `-A`: enable thread affinity
     - `-h`: help

7. **Thread Affinity** (`-A`)

   - Optional binding of producer/consumer threads to CPU cores

## Requirements

- C++17 or higher
- CMake (>= 3.10)
- `make`

## Build Instructions

```bash
git clone <repo_url>
cd ProducerConsumerEngine
mkdir build && cd build
cmake ..
make
```
