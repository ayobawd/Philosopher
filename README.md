# 🍽️ Philosophers - The Dining Philosophers Problem

## 📖 Project Overview

This project is an implementation of the classic **Dining Philosophers Problem** in C, solving it using threads and mutexes. It's a fundamental computer science problem that demonstrates concepts of concurrency, synchronization, deadlock prevention, and resource sharing.

### 🎯 What is the Dining Philosophers Problem?

Imagine philosophers sitting around a circular table with a bowl of spaghetti. Between each pair of philosophers, there's exactly one fork. A philosopher needs **two forks** to eat, but can only pick up the forks immediately to their left and right.

**The Challenge**: How do we ensure that:
- Philosophers don't starve (everyone gets to eat)
- No deadlocks occur (everyone waiting for someone else)
- No race conditions happen (proper synchronization)

---

## 🚀 Quick Start

### Prerequisites
- GCC compiler
- POSIX-compliant system (Linux, macOS)
- pthread library support

### Installation & Compilation

```bash
# Clone the repository
git clone <repository-url>
cd Philosopher

# Compile the project
make

# The executable 'philo' will be created
```

### Basic Usage

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_meals]
```

**Parameters (all times in milliseconds):**
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time before a philosopher dies from hunger
- `time_to_eat`: Time it takes to eat
- `time_to_sleep`: Time spent sleeping
- `number_of_meals`: (Optional) Simulation stops when all philosophers have eaten this many times

### Example Commands

```bash
# Basic simulation - 5 philosophers, should run indefinitely without deaths
./philo 5 800 200 200

# With meal limit - stops when all philosophers eat 7 times
./philo 5 800 200 200 7

# Edge case - single philosopher (will die as they can't get two forks)
./philo 1 800 200 200

# Quick death scenario for testing
./philo 4 310 200 100
```

---

## 🏗️ Project Architecture

### Data Structures

#### `t_rules` - Global Simulation Rules
```c
typedef struct s_rules {
    int           n;              // Number of philosophers
    int           t_die;          // Time to die (ms)
    int           t_eat;          // Time to eat (ms)
    int           t_sleep;        // Time to sleep (ms)
    int           eat_goal;       // Optional meal limit (-1 if none)
    long long     start_ms;       // Simulation start timestamp
    int           alive;          // Global alive flag
    int           done_count;     // Count of philosophers who reached meal goal
    t_mtx         print;          // Mutex for synchronized printing
    t_mtx         *forks;         // Array of fork mutexes
    t_mtx         meal_mtx;       // Mutex for meal-related data
    t_mtx         mtx_alive;      // Mutex for alive flag
    t_mtx         mtx_done;       // Mutex for done count
} t_rules;
```

#### `t_philo` - Individual Philosopher
```c
typedef struct s_philo {
    int           id;             // Philosopher ID (1 to n)
    int           left;           // Left fork index
    int           right;          // Right fork index
    long long     last_meal_ms;   // Timestamp of last meal
    int           meals_eaten;    // Number of meals consumed
    t_rules       *rules;         // Pointer to shared rules
    pthread_t     thread_id;      // Thread identifier
} t_philo;
```

### Threading Model

The program creates **n + 1** threads:
- **n philosopher threads**: Each philosopher runs in their own thread
- **1 monitor thread**: Watches for deaths and meal completion

---

## 📁 File Structure & Responsibilities

### Core Files

| File | Purpose | Key Functions |
|------|---------|---------------|
| `main.c` | Program entry point | `main()` - orchestrates the entire simulation |
| `philo.h` | Header file | Contains all structures, includes, and function declarations |

### Initialization & Setup
| File | Purpose | Key Functions |
|------|---------|---------------|
| `init.c` | Data structure initialization | `init_rules()`, `philo()`, `data_init()` |
| `parsing.c` | Argument validation & parsing | `validate_arguments()`, `handle_single_philo()` |

### Core Logic
| File | Purpose | Key Functions |
|------|---------|---------------|
| `routine.c` | Main philosopher behavior | `routine()`, `take_forks()`, `print_action()` |
| `routine_helper.c` | Eating and fork management | `philo_eat()`, `drop_forks()` |
| `simulation.c` | Monitoring and death detection | `monitor_routine()`, `check_philosopher_death()` |

### Utilities
| File | Purpose | Key Functions |
|------|---------|---------------|
| `time_utils.c` | Time management | `now_ms()`, `smart_usleep()`, `check_alive()` |
| `utlis.c` | String utilities | `ft_atoi()`, `ft_isdigit()` |
| `handle_errors.c` | Memory & error management | `free_all()`, `safe_malloc()`, `error_exit()` |

---

## 🔄 Program Flow

### 1. Initialization Phase
```
main() → argument validation → philosopher creation → mutex initialization
```

### 2. Simulation Phase
```
Fork Creation:
├── Monitor Thread (death/completion checking)
└── Philosopher Threads (eating cycle)
```

### 3. Philosopher Life Cycle
```
THINKING → TAKING FORKS → EATING → SLEEPING → (repeat)
```

### 4. Termination
```
Death detected OR all meals completed → cleanup → exit
```

---

## 🔐 Synchronization Strategy

### Deadlock Prevention: **Odd/Even Fork Strategy**

To prevent circular waiting (deadlock), philosophers pick up forks in different orders:

```c
if (philosopher_id % 2 == 0) {
    // Even philosophers: right fork first, then left
    lock(right_fork);
    lock(left_fork);
} else {
    // Odd philosophers: left fork first, then right
    lock(left_fork);
    lock(right_fork);
}
```

### Mutex Protection Areas

| Mutex | Protects | Why It's Needed |
|-------|----------|-----------------|
| `print` | Console output | Prevents message interleaving |
| `forks[i]` | Individual forks | Ensures exclusive fork access |
| `meal_mtx` | Meal timestamps & counts | Prevents race conditions in meal data |
| `mtx_alive` | Global alive flag | Thread-safe simulation termination |
| `mtx_done` | Meal completion counter | Safe tracking of completion |

---

## ⚙️ Key Algorithms

### Smart Sleep Function
Instead of simple `usleep()`, we use `smart_usleep()` that:
- Checks the alive flag periodically
- Prevents oversleeping when simulation should stop
- Uses small sleep intervals (200μs) for responsiveness

```c
void smart_usleep(long long ms, t_rules *r) {
    long long start = now_ms();
    while (check_alive(r)) {
        if (now_ms() - start >= ms) break;
        usleep(200);  // Sleep in small chunks
    }
}
```

### Death Detection
The monitor thread continuously checks if any philosopher has exceeded their time limit:

```c
time_since_last_meal = current_time - philosopher.last_meal_ms;
if (time_since_last_meal > time_to_die) {
    // Philosopher has died!
}
```

---

## 🧪 Testing Scenarios

### 1. **No Death Scenarios** (Should run indefinitely)
```bash
./philo 5 800 200 200    # Comfortable timing
./philo 5 600 200 200    # Tighter timing
./philo 4 410 200 200    # Even tighter
```

### 2. **Death Scenarios**
```bash
./philo 1 800 200 200    # Single philosopher (impossible to eat)
./philo 4 310 200 100    # Very tight timing, death likely
```

### 3. **Meal Limit Scenarios**
```bash
./philo 5 800 200 200 7  # Stop after everyone eats 7 times
./philo 2 800 200 200 3  # Simple case with 2 philosophers
```

### 4. **Edge Cases**
```bash
./philo 1 400 200 200    # Single philosopher edge case
./philo 2 500 200 200    # Minimum for actual eating
```

---

## 📊 Output Format

Each action is logged with precise timing:

```
<timestamp_ms> <philosopher_id> <action>
```

**Example Output:**
```
0 1 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
401 2 has taken a fork
401 2 has taken a fork
401 2 is eating
```

**Possible Actions:**
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

---

## 🛠️ Build System

### Makefile Targets

```bash
make          # Build the project
make all      # Same as make
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Clean and rebuild
```

### Compilation Flags
- `-Wall -Wextra -Werror`: Strict warning settings
- `-g`: Debug information
- `-lpthread`: Link pthread library

---

## 🚨 Common Issues & Troubleshooting

### Compilation Issues
- **Missing pthread**: Install build essentials on your system
- **Norm errors**: Code follows 42 school norminette standards

### Runtime Issues
- **Immediate death**: Check your timing parameters
- **No output**: Verify parameters are positive integers
- **Segmentation fault**: Usually indicates memory allocation issues

### Understanding the Output
- **Overlapping timestamps**: Normal - multiple philosophers act simultaneously
- **"died" message**: Simulation ends when any philosopher dies
- **No "died" message with meal limit**: Simulation completed successfully

---

## 🎓 Learning Concepts

This project teaches essential computer science concepts:

### Threading Concepts
- **Thread creation and management** (`pthread_create`, `pthread_join`)
- **Thread synchronization** with mutexes
- **Race condition prevention**

### Synchronization Primitives
- **Mutex locks** for critical sections
- **Deadlock prevention** strategies
- **Resource allocation** algorithms

### System Programming
- **Time measurement** with `gettimeofday()`
- **Memory management** (allocation and cleanup)
- **Process timing** and scheduling

### Problem-Solving Patterns
- **Producer-consumer** problem variations
- **Resource sharing** among multiple processes
- **Concurrent programming** patterns

---

## 🔍 Advanced Topics

### Why This Approach?

1. **Odd/Even Strategy**: Breaks the circular wait condition of deadlock
2. **Multiple Mutexes**: Granular locking reduces contention
3. **Monitor Pattern**: Separates concern of death detection from eating logic
4. **Smart Sleep**: Responsive to simulation state changes

### Performance Considerations

- **Mutex Granularity**: Balance between safety and performance
- **Sleep Intervals**: Trade-off between CPU usage and responsiveness
- **Memory Layout**: Structures optimized for cache efficiency

### Alternative Approaches

This implementation could be modified to use:
- **Semaphores** instead of mutexes
- **Process-based** instead of thread-based concurrency
- **Different deadlock prevention** strategies (like resource ordering)

---

## 📚 Further Reading

- **Operating System Concepts** by Silberschatz, Galvin, and Gagne
- **The Little Book of Semaphores** by Allen B. Downey
- **POSIX Threads Programming** documentation
- **Dining Philosophers Problem** variations and solutions

---

## 🤝 Contributing

This is an educational project following 42 school standards. The code adheres to:
- **Norminette** coding standards
- **No global variables** policy
- **Specific function limitations** (≤25 lines, ≤5 functions per file)
- **Memory leak prevention**

---

*This README aims to make the Dining Philosophers problem and its implementation accessible to programmers at all levels. The project demonstrates fundamental concepts in concurrent programming and serves as an excellent introduction to threading and synchronization challenges.*