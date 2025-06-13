# Philosophers

## Introduction

The *Philosophers* project is a simulation of the classic Dining Philosophers Problem. It involves managing multiple philosophers who alternate between eating, sleeping, and thinking, all while avoiding deadlocks and starvation.

---


philo/
├── Makefile
├── philo.h
├── main.c
├── init.c
├── routine.c
├── utils.c
├── time.c
└── monitor.c


## Table of Contents
- [Introduction](#introduction)
- [Requirements](#requirements)
- [Overview](#overview)
- [Execution Rules](#execution-rules)
- [Implementation Details](#implementation-details)
- [Compilation](#compilation)
- [Usage](#usage)
- [Resources](#resources)

---

## Requirements

- Written in C
- Follow the [42 Norm](https://github.com/42School/norminette)
- No memory leaks (all allocated memory must be freed)
- Must not use global variables
- All logs must be properly synchronized (no mixed output)
- Must not crash (no segmentation faults, etc.)
- Use only allowed C functions
- Use pthreads and mutexes

---

## Overview

- Philosophers sit at a round table with one fork between each pair.
- They must pick up both forks to eat.
- After eating, they sleep, then think.
- If a philosopher doesn't eat within `time_to_die`, they die.
- The simulation stops when a philosopher dies or when every philosopher has eaten `number_of_times_each_philosopher_must_eat` times (if provided).

---

## Execution Rules

### Arguments
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Max time (ms) a philosopher can stay without eating
- `time_to_eat`: Time (ms) a philosopher takes to eat
- `time_to_sleep`: Time (ms) a philosopher sleeps after eating
- `number_of_times_each_philosopher_must_eat` (optional): Simulation stops when all have eaten this many times

### Output Format

timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died


All output must be properly synchronized using mutexes.

---

## Implementation Details

- Each philosopher is represented by a **thread**.
- Forks are represented as **mutexes**.
- Access to shared resources (e.g., printing, death check) is protected.
- The main thread creates all philosopher threads and monitors their status.
- No philosopher should die unexpectedly (unless starvation is intended).
- If there is only one philosopher, he picks up one fork and dies.

---

## Compilation
make # Compile the mandatory part
make clean # Remove object files
make fclean # Remove all binaries
make re # Recompile from scratch


---

## Usage

Run with 5 philosophers:

./philo 5 800 200 200

Run with a limit on meals:

./philo 5 800 200 200 3

This simulates 5 philosophers, where each must eat at least 3 times. The simulation ends when this is achieved.

---

**a small explanation*********************************************************************************************************************************************
🧵 Main thread = the main() function

This is the original thread that runs your program. It will:

    Create a thread for each philosopher using pthread_create.

    Start a "monitor" function, which:

        Regularly checks if any philosopher has not eaten within time_to_die → then it logs "X died" and stops the simulation.

        If the optional argument number_of_times_each_philosopher_must_eat is provided, it also checks whether all philosophers have eaten enough times → and then stops the simulation cleanly.

🔍 Why do we need this monitor?

Philosophers do not communicate, and threads can’t "detect death" on their own. So the main thread acts like a referee:

    It loops every few milliseconds.

    It checks the last_meal_time of each philosopher (protected with a mutex).

    If the time since last meal > time_to_die, it:

        Prints the death log,

        Sets a shared stop_simulation flag,

        Ends the simulation.
*************************************************************************************************************************************************************


🧪 Evaluation Criteria & Defense Expectations

This section summarizes how your Philosophers project will be evaluated during the official peer defense at 1337/42 school:
✅ General Guidelines

    Your code must strictly follow the Norm. Any norm error = 0.

    No crashes, segmentation faults, or undefined behavior. If your program crashes = 0.

    Memory leaks are forbidden. Valgrind or leaks tools will be used to verify this.

    Global variables are strictly forbidden.

    Evaluation is based only on what’s in your Git repository. The evaluator will git clone in an empty directory and check your work.

👥 Peer Evaluation Rules

    The evaluator must remain respectful, honest, and constructive.

    Both the evaluator and the student should be familiar with the subject and evaluation criteria.

    Evaluation must stop immediately in case of:

        Empty repository

        Norm errors

        Crashes or undefined behavior

        Memory leaks

        Any attempt to cheat (evaluated as -42)

⚙️ What Will Be Checked
🔩 Code & Structure

    One thread per philosopher.

    One fork between each pair of philosophers (total forks = number of philosophers).

    Each fork must be protected with a mutex.

    Output logs must not be scrambled.

    Death detection must be mutex-protected, so a philosopher cannot eat and die at the same time.

    Philosopher states (eating, sleeping, thinking) must print in the correct format and be precisely timestamped.

    No data races.

🧪 Runtime Tests

The following tests are often used by evaluators. You should make sure these all pass:
Command	Expected Result
./philo 1 800 200 200	Philosopher dies (cannot eat with 1 fork)
./philo 5 800 200 200	No one dies
./philo 5 800 200 200 7	All eat 7 times, simulation stops
./philo 4 410 200 200	No one dies
./philo 4 310 200 100	One should die
./philo 2 200 100 100	Test time precision; no delays >10ms in death
Do not test with more than 200 philosophers.
Do not use sleep/eat/die values under 60ms unless you’re confident in your timing accuracy.

***********************************************************************************************************************************
## Resources

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads (pthreads)](https://man7.org/linux/man-pages/man7/pthreads.7.html)

---

> Made with ❤️ at 1337 School by imiqor(iman iqor).
