# Philosophers

A solution to the classic dining philosophers problem using threads and mutexes in C.

## Description

This program simulates the dining philosophers problem where N philosophers sit around a circular table with N forks. Each philosopher needs two forks to eat, creating a classic synchronization problem.

## Features

- Deterministic, race-free implementation
- Monitor thread for death detection within 10ms
- Proper deadlock prevention using ordered fork acquisition
- Memory leak-free implementation
- Norminette compliant code

## Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds before a philosopher dies of starvation
- `time_to_eat`: Time in milliseconds a philosopher takes to eat
- `time_to_sleep`: Time in milliseconds a philosopher sleeps
- `number_of_times_each_philosopher_must_eat`: Optional. Program stops when all philosophers have eaten this many times

## Test Cases

### No-death scenarios (should run ≥10s without deaths):
```bash
./philo 5 800 200 200
./philo 5 600 200 200
./philo 4 410 200 200
```

### Death scenario:
```bash
./philo 1 800 200 200
# Single philosopher can only take one fork and dies at time_to_die
```

### Meal goal completion:
```bash
./philo 5 800 200 200 7
# Program stops when all philosophers have eaten 7 times
```

### Death detection:
```bash
./philo 4 310 200 100
# Tight timing that should cause a death
```

## Output Format

Each state change produces a log line:
```
<timestamp_ms> <philosopher_id> has taken a fork
<timestamp_ms> <philosopher_id> is eating
<timestamp_ms> <philosopher_id> is sleeping
<timestamp_ms> <philosopher_id> is thinking
<timestamp_ms> <philosopher_id> died
```

- `timestamp_ms` is relative to program start
- No interleaving between log lines
- Death is printed within 10ms of actual death
- No logs after death message

## Architecture

- **Monitor thread**: Checks for deaths every ~1ms and meal goal completion
- **Philosopher threads**: One per philosopher, handles eating/sleeping/thinking cycle
- **Deadlock prevention**: Even-numbered philosophers take right fork first, odd-numbered take left fork first
- **Race condition prevention**: All shared data access protected by mutexes

## Build

```bash
make        # Build the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild everything
```

## Memory Management

The program properly cleans up all allocated memory and destroys all mutexes on exit. Tested with valgrind to ensure no memory leaks.