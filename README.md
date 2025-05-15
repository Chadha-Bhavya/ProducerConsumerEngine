# ProducerConsumerEngine

A terminal-based simulation of a multithreaded producer–consumer system in C++.

## Purpose

Demonstrate concurrency concepts using C++17 and standard threading tools:

- Bounded buffer with priority scheduling
- Starvation prevention via task aging
- Thread affinity and deadlock simulation
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
     - `-D`: simulate deadlock demo
     - `-h`: help

7. **Thread Affinity** (`-A`)

   - Optional binding of producer/consumer threads to CPU cores

8. **Deadlock Simulation** (`-D`)

   - Two worker threads lock resources in opposite order
   - Detector thread identifies deadlock and triggers shutdown

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

## Usage

```bash
# Run with defaults:
./simulation

# Customize parameters:
./simulation -p 4 -c 5 -q 20 -r 30 -m 10

# Enable thread affinity and deadlock demo:
./simulation -A -D

# Show help:
./simulation -h
```

## Example Output

```
[Config] p=2 c=3 q=10 r=20 m=5
[Producer 0] Created Task 0 (prio=4)
[Consumer 1] Processing Task 0
[Producer 1] Created Task 1 (prio=1)
[Consumer 2] Processing Task 1
[Producer 0] Created Task 2 (prio=5)
[Consumer 0] Processing Task 2
[Producer 1] Created Task 3 (prio=4)
[Consumer 1] Processing Task 3
[Producer 0] Created Task 4 (prio=4)
[Consumer 2] Processing Task 4
[Consumer 0] Processing Task 5
[Producer 1] Created Task 5 (prio=4)
[Producer 0] Created Task 6 (prio=5)
[Consumer 1] Processing Task 6
[Producer 1] Created Task 7 (prio=4)
[Consumer 2] Processing Task 7
[Monitor] Aged all tasks
[Producer 0] Created Task 8 (prio=3)
[Consumer 0] Processing Task 8
[Producer 1] Created Task 9 (prio=3)
[Consumer 1] Processing Task 9
[Producer 0] Created Task 10 (prio=3)
[Consumer 2] Processing Task 10
[Producer 1] Created Task 11 (prio=2)
[Consumer 0] Processing Task 11
[Producer 1] Created Task 12 (prio=2)
[Consumer 1] Processing Task 12
[Producer 0] Created Task 13 (prio=2)
[Consumer 2] Processing Task 13
[Producer 1] Created Task 14 (prio=5)
[Consumer 0] Processing Task 14
[Producer 0] Created Task 15 (prio=3)
[Consumer 1] Processing Task 15
[Producer 0] Created Task 16 (prio=2)
[Consumer 2] Processing Task 16
[Monitor] Aged all tasks
[Producer 1] Created Task 17 (prio=1)
[Consumer 0] Processing Task 17
[Producer 0] Created Task 18 (prio=4)
[Consumer 1] Processing Task 18
[Producer 0] Created Task 19 (prio=4)
[Consumer 2] Processing Task 19
[Producer 1] Created Task 20 (prio=4)
[Consumer 0] Processing Task 20
[Producer 1] Created Task 21 (prio=2)
[Consumer 1] Processing Task 21
[Producer 0] Created Task 22 (prio=5)
[Consumer 2] Processing Task 22
[Producer 1] Created Task 23 (prio=2)
[Consumer 0] Processing Task 23
[Producer 0] Created Task 24 (prio=1)
[Consumer 1] Processing Task 24
[Producer 1] Created Task 25 (prio=5)
[Consumer 2] Processing Task 25
[Producer 0] Created Task 26 (prio=3)
[Consumer 0] Processing Task 26
[Monitor] Aged all tasks
[Producer 1] Created Task 27 (prio=3)
[Consumer 1] Processing Task 27
[Producer 0] Created Task 28 (prio=4)
[Consumer 2] Processing Task 28
[Producer 1] Created Task 29 (prio=2)
[Consumer 0] Processing Task 29
[Producer 0] Created Task 30 (prio=3)
[Consumer 1] Processing Task 30
[Producer 0] Created Task 31 (prio=4)
[Consumer 2] Processing Task 31
[Producer 0] Created Task 32 (prio=5)
[Consumer 0] Processing Task 32
[Producer 1] Created Task 33 (prio=5)
[Consumer 1] Processing Task 33
[Producer 0] Created Task 34 (prio=2)
[Consumer 2] Processing Task 34
[Producer 1] Created Task 35 (prio=2)
[Consumer 0] Processing Task 35
[Producer 0] Created Task 36 (prio=3)
[Consumer 1] Processing Task 36
[Consumer 2] Processing Task 37
[Producer 1] Created Task 37 (prio=1)
[Monitor] Aged all tasks
[Producer 0] Created Task 38 (prio=2)
[Consumer 0] Processing Task 38
[Producer 1] Created Task 39 (prio=5)
[Consumer 1] Processing Task 39
[Producer 1] Created Task 40 (prio=1)
[Consumer 2] Processing Task 40
[Producer 0] Created Task 41 (prio=2)
[Consumer 0] Processing Task 41
[Producer 1] Created Task 42 (prio=3)
[Consumer 1] Processing Task 42
[Producer 0] Created Task 43 (prio=1)
[Consumer 2] Processing Task 43
[Producer 1] Created Task 44 (prio=3)
[Consumer 0] Processing Task 44
[Producer 0] Created Task 45 (prio=4)
[Consumer 1] Processing Task 45
[Producer 1] Created Task 46 (prio=1)
[Consumer 2] Processing Task 46
[Monitor] Aged all tasks
[Producer 0] Created Task 47 (prio=4)
[Consumer 0] Processing Task 47
[Producer 1] Created Task 48 (prio=2)
[Consumer 1] Processing Task 48
[Producer 0] Created Task 49 (prio=2)
[Consumer 2] Processing Task 49
[Producer 1] Created Task 50 (prio=3)
[Consumer 0] Processing Task 50
[Producer 0] Created Task 51 (prio=2)
[Consumer 1] Processing Task 51
[Producer 1] Created Task 52 (prio=4)
[Consumer 2] Processing Task 52
[Producer 1] Created Task 53 (prio=5)
[Consumer 0] Processing Task 53
[Producer 0] Created Task 54 (prio=1)
[Consumer 1] Processing Task 54
[Monitor] Aged all tasks
[Producer 1] Created Task 55 (prio=1)
[Consumer 2] Processing Task 55
[Producer 0] Created Task 56 (prio=4)
[Consumer 0] Processing Task 56
[Producer 1] Created Task 57 (prio=3)
[Consumer 1] Processing Task 57
[Producer 0] Created Task 58 (prio=1)
[Consumer 2] Processing Task 58
[Producer 1] Created Task 59 (prio=3)
[Consumer 0] Processing Task 59
[Producer 0] Created Task 60 (prio=3)
[Consumer 1] Processing Task 60
[Producer 0] Created Task 61 (prio=2)
[Consumer 2] Processing Task 61
[Producer 1] Created Task 62 (prio=4)
[Consumer 0] Processing Task 62
[Producer 0] Created Task 63 (prio=5)
[Consumer 1] Processing Task 63
[Producer 1] Created Task 64 (prio=5)
[Consumer 2] Processing Task 64
[Producer 1] Created Task 65 (prio=4)
[Producer 0] Created Task 66 (prio=2)
[Consumer 0] Processing Task 65
[Consumer 1] Processing Task 66
[Monitor] Aged all tasks
[Producer 0] Created Task 67 (prio=2)
[Consumer 2] Processing Task 67
[Producer 1] Created Task 68 (prio=1)
[Consumer 0] Processing Task 68
[Producer 0] Created Task 69 (prio=4)
[Consumer 1] Processing Task 69
[Producer 1] Created Task 70 (prio=1)
[Consumer 2] Processing Task 70
[Producer 0] Created Task 71 (prio=2)
[Consumer 0] Processing Task 71
[Producer 1] Created Task 72 (prio=5)
[Consumer 1] Processing Task 72
[Producer 0] Created Task 73 (prio=1)
[Consumer 2] Processing Task 73
[Consumer 0] Processing Task 74
[Producer 0] Created Task 74 (prio=4)
[Producer 1] Created Task 75 (prio=3)
[Consumer 1] Processing Task 75
[Monitor] Aged all tasks
[Producer 0] Created Task 76 (prio=1)
[Consumer 2] Processing Task 76
[Producer 1] Created Task 77 (prio=1)
[Consumer 0] Processing Task 77
[Producer 1] Created Task 78 (prio=1)
[Consumer 1] Processing Task 78
[Producer 0] Created Task 79 (prio=3)
[Consumer 2] Processing Task 79
[Producer 1] Created Task 80 (prio=1)
[Consumer 0] Processing Task 80
[Producer 0] Created Task 81 (prio=3)
[Consumer 1] Processing Task 81
[Producer 1] Created Task 82 (prio=3)
[Consumer 2] Processing Task 82
[Producer 0] Created Task 83 (prio=2)
[Consumer 0] Processing Task 83
[Monitor] Aged all tasks
[Producer 1] Created Task 84 (prio=3)
[Consumer 1] Processing Task 84
[Producer 1] Created Task 85 (prio=4)
[Consumer 2] Processing Task 85
[Producer 0] Created Task 86 (prio=4)
[Consumer 0] Processing Task 86
[Producer 0] Created Task 87 (prio=1)
[Consumer 1] Processing Task 87
[Producer 1] Created Task 88 (prio=1)
[Consumer 2] Processing Task 88
[Producer 0] Created Task 89 (prio=5)
[Consumer 0] Processing Task 89
[Producer 1] Created Task 90 (prio=2)
[Consumer 1] Processing Task 90
[Producer 1] Created Task 91 (prio=1)
[Consumer 2] Processing Task 91
[Producer 0] Created Task 92 (prio=5)
[Consumer 0] Processing Task 92
[Producer 1] Created Task 93 (prio=2)
[Consumer 1] Processing Task 93
[Monitor] Aged all tasks
[Producer 1] Created Task 94 (prio=5)
[Consumer 2] Processing Task 94
[Producer 0] Created Task 95 (prio=1)
[Consumer 0] Processing Task 95
[Producer 1] Created Task 96 (prio=5)
[Consumer 1] Processing Task 96
[Producer 0] Created Task 97 (prio=5)
[Consumer 2] Processing Task 97
[Producer 0] Created Task 98 (prio=3)
[Consumer 0] Processing Task 98
[Producer 1] Created Task 99 (prio=2)
[Consumer 1] Processing Task 99
[Producer 0] Created Task 100 (prio=3)
[Consumer 2] Processing Task 100
[Producer 1] Created Task 101 (prio=4)
[Consumer 0] Processing Task 101
[Producer 1] Created Task 102 (prio=2)
[Consumer 1] Processing Task 102
[Producer 0] Created Task 103 (prio=2)
[Monitor] Aged all tasks
[Consumer 2] Processing Task 103
[Producer 1] Created Task 104 (prio=5)
[Consumer 0] Processing Task 104
[Producer 0] Created Task 105 (prio=4)
[Consumer 1] Processing Task 105
[Producer 1] Created Task 106 (prio=5)
[Consumer 2] Processing Task 106
[Producer 1] Created Task 107 (prio=1)
[Consumer 0] Processing Task 107
[Producer 0] Created Task 108 (prio=3)
[Consumer 1] Processing Task 108
[Producer 1] Created Task 109 (prio=1)
[Consumer 2] Processing Task 109
[Producer 0] Created Task 110 (prio=2)
[Consumer 0] Processing Task 110
[Producer 1] Created Task 111 (prio=4)
[Consumer 1] Processing Task 111
[Producer 1] Created Task 112 (prio=2)
[Consumer 2] Processing Task 112
[Producer 0] Created Task 113 (prio=2)
[Consumer 0] Processing Task 113
[Monitor] Aged all tasks
[Producer 1] Created Task 114 (prio=2)
[Consumer 1] Processing Task 114
[Producer 1] Created Task 115 (prio=5)
[Consumer 2] Processing Task 115
[Producer 0] Created Task 116 (prio=1)
[Consumer 0] Processing Task 116
[Producer 0] Created Task 117 (prio=3)
[Consumer 1] Processing Task 117
[Producer 1] Created Task 118 (prio=4)
[Consumer 2] Processing Task 118
[Producer 0] Created Task 119 (prio=3)
[Consumer 0] Processing Task 119
[Producer 1] Created Task 120 (prio=1)
[Consumer 1] Processing Task 120
[Producer 0] Created Task 121 (prio=1)
[Consumer 2] Processing Task 121
[Producer 1] Created Task 122 (prio=4)
[Consumer 0] Processing Task 122
[Monitor] Aged all tasks
[Producer 0] Created Task 123 (prio=4)
[Consumer 1] Processing Task 123
[Producer 1] Created Task 124 (prio=2)
[Consumer 2] Processing Task 124
[Producer 0] Created Task 125 (prio=1)
[Consumer 0] Processing Task 125
[Producer 0] Created Task 126 (prio=1)
[Consumer 1] Processing Task 126
[Producer 1] Created Task 127 (prio=3)
[Consumer 2] Processing Task 127
[Producer 0] Created Task 128 (prio=3)
[Consumer 0] Processing Task 128
[Producer 1] Created Task 129 (prio=5)
[Consumer 1] Processing Task 129
[Producer 1] Created Task 130 (prio=4)
[Consumer 2] Processing Task 130
[Producer 0] Created Task 131 (prio=5)
[Consumer 0] Processing Task 131
[Producer 1] Created Task 132 (prio=2)
[Consumer 1] Processing Task 132
[Monitor] Aged all tasks
[Producer 0] Created Task 133 (prio=5)
[Consumer 2] Processing Task 133
[Producer 1] Created Task 134 (prio=2)
[Consumer 0] Processing Task 134
[Producer 0] Created Task 135 (prio=3)
[Consumer 1] Processing Task 135
[Producer 1] Created Task 136 (prio=5)
[Consumer 2] Processing Task 136
[Producer 0] Created Task 137 (prio=1)
[Consumer 0] Processing Task 137
[Producer 1] Created Task 138 (prio=1)
[Consumer 1] Processing Task 138
[Producer 0] Created Task 139 (prio=2)
[Consumer 2] Processing Task 139
[Producer 1] Created Task 140 (prio=3)
[Consumer 0] Processing Task 140
[Producer 0] Created Task 141 (prio=2)
[Consumer 1] Processing Task 141
[Producer 1] Created Task 142 (prio=5)
[Consumer 2] Processing Task 142
[Monitor] Aged all tasks
[Producer 0] Created Task 143 (prio=2)
[Consumer 0] Processing Task 143
[Producer 1] Created Task 144 (prio=5)
[Consumer 1] Processing Task 144
[Producer 0] Created Task 145 (prio=1)
[Consumer 2] Processing Task 145
[Producer 1] Created Task 146 (prio=5)
[Consumer 0] Processing Task 146
[Producer 0] Created Task 147 (prio=1)
[Consumer 1] Processing Task 147
[Producer 1] Created Task 148 (prio=3)
[Consumer 2] Processing Task 148
[Producer 0] Created Task 149 (prio=2)
[Consumer 0] Processing Task 149
[Producer 1] Created Task 150 (prio=2)
[Consumer 1] Processing Task 150
[Producer 0] Created Task 151 (prio=2)
[Consumer 2] Processing Task 151
[Producer 1] Created Task 152 (prio=2)
[Consumer 0] Processing Task 152
[Producer 0] Created Task 153 (prio=5)
[Consumer 1] Processing Task 153
[Producer 0] Created Task 154 (prio=1)
[Consumer 2] Processing Task 154
[Monitor] Aged all tasks
[Producer 1] Created Task 155 (prio=3)
[Consumer 0] Processing Task 155
[Producer 0] Created Task 156 (prio=4)
[Consumer 1] Processing Task 156
[Producer 1] Created Task 157 (prio=3)
[Consumer 2] Processing Task 157
[Producer 0] Created Task 158 (prio=5)
[Consumer 0] Processing Task 158
[Producer 1] Created Task 159 (prio=4)
[Consumer 1] Processing Task 159
[Producer 0] Created Task 160 (prio=2)
[Consumer 2] Processing Task 160
[Producer 1] Created Task 161 (prio=3)
[Consumer 0] Processing Task 161
[Producer 0] Created Task 162 (prio=3)
[Consumer 1] Processing Task 162
[Consumer 2] Processing Task 163
[Producer 1] Created Task 163 (prio=3)
[Producer 0] Created Task 164 (prio=1)
[Consumer 0] Processing Task 164
[Monitor] Aged all tasks
[Producer 1] Created Task 165 (prio=3)
[Consumer 1] Processing Task 165
[Producer 0] Created Task 166 (prio=2)
[Consumer 2] Processing Task 166
[Producer 1] Created Task 167 (prio=2)
[Consumer 0] Processing Task 167
[Producer 0] Created Task 168 (prio=5)
[Consumer 1] Processing Task 168
[Producer 1] Created Task 169 (prio=5)
[Consumer 2] Processing Task 169
[Producer 0] Created Task 170 (prio=5)
[Consumer 0] Processing Task 170
[Producer 1] Created Task 171 (prio=5)
[Consumer 1] Processing Task 171
[Producer 0] Created Task 172 (prio=1)
[Consumer 2] Processing Task 172
[Producer 1] Created Task 173 (prio=5)
[Consumer 0] Processing Task 173
[Producer 0] Created Task 174 (prio=2)
[Consumer 1] Processing Task 174
[Monitor] Aged all tasks
[Producer 1] Created Task 175 (prio=5)
[Consumer 2] Processing Task 175
[Producer 0] Created Task 176 (prio=4)
[Consumer 0] Processing Task 176
[Producer 1] Created Task 177 (prio=2)
[Consumer 1] Processing Task 177
[Producer 1] Created Task 178 (prio=1)
[Consumer 2] Processing Task 178
[Producer 0] Created Task 179 (prio=5)
[Consumer 0] Processing Task 179
[Producer 1] Created Task 180 (prio=5)
[Consumer 1] Processing Task 180
[Producer 0] Created Task 181 (prio=1)
[Consumer 2] Processing Task 181
[Producer 1] Created Task 182 (prio=3)
[Consumer 0] Processing Task 182
[Producer 1] Created Task 183 (prio=3)
[Consumer 1] Processing Task 183
[Producer 0] Created Task 184 (prio=1)
[Consumer 2] Processing Task 184
[Producer 1] Created Task 185 (prio=3)
[Consumer 0] Processing Task 185
[Monitor] Aged all tasks
[Producer 1] Created Task 186 (prio=3)
[Consumer 1] Processing Task 186
[Producer 0] Created Task 187 (prio=4)
[Consumer 2] Processing Task 187
[Producer 0] Created Task 188 (prio=3)
[Consumer 0] Processing Task 188
[Producer 1] Created Task 189 (prio=1)
[Consumer 1] Processing Task 189
[Producer 1] Created Task 190 (prio=1)
[Consumer 2] Processing Task 190
[Producer 0] Created Task 191 (prio=4)
[Consumer 0] Processing Task 191
[Consumer 1] Processing Task 192
[Producer 1] Created Task 192 (prio=2)
[Producer 0] Created Task 193 (prio=2)
[Consumer 2] Processing Task 193
[Producer 1] Created Task 194 (prio=1)
[Consumer 0] Processing Task 194
[Producer 0] Created Task 195 (prio=1)
[Consumer 1] Processing Task 195
[Producer 1] Created Task 196 (prio=5)
[Consumer 2] Processing Task 196
[Monitor] Aged all tasks
[Producer 0] Created Task 197 (prio=2)
[Consumer 1] Processing Task 197
[Producer 1] Created Task 198 (prio=3)
[Consumer 2] Processing Task 198
Simulation ended cleanly.
```

## Concepts Demonstrated

- Thread creation and synchronization (`std::thread`, `std::mutex`, `std::condition_variable`)
- Priority scheduling and starvation prevention
- Safe shutdown coordination
- Thread affinity (`pthread_setaffinity_np` / macOS APIs)
- Deadlock detection and recovery

---

© 2025 ProducerConsumerEngine
