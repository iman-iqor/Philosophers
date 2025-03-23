Philosophers
Introduction
The Philosophers project is a simulation of the classic "Dining Philosophers" problem. The goal is to manage the behavior of multiple philosophers sitting around a table, ensuring that they can eat, think, and sleep without causing deadlocks or starvation.
Table of Contents
* Introduction
* Common Instructions
* Overview
* Global Rules
* Mandatory Part
* Bonus Part
* How to Compile
* How to Run
* Resources
Common Instructions
* The project must be written in C and follow the 42 Norm.
* No memory leaks are allowed (all allocated memory must be freed correctly).
* The program must handle errors properly and not crash unexpectedly.
* The project must include a Makefile with the following rules:
    * make: Compiles the program.
    * make clean: Removes object files.
    * make fclean: Removes object files and executables.
    * make re: Recompiles the project.
    * make bonus: Compiles the bonus part.
Overview
* Philosophers sit at a round table and share a large bowl of spaghetti.
* Each philosopher can eat, think, or sleep.
* To eat, a philosopher must take two forks (one in each hand).
* If a philosopher does not eat within a given time_to_die, they die.
* The simulation stops when a philosopher dies or when all have eaten a specified number of times (if provided as an argument).
Global Rules
* Global variables are forbidden.
* The program must take the following arguments: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
* The logs must follow a specific format: timestamp_in_ms X has taken a fork
* timestamp_in_ms X is eating
* timestamp_in_ms X is sleeping
* timestamp_in_ms X is thinking
* timestamp_in_ms X died
* The program must ensure no data races occur.
Mandatory Part
* The mandatory part implements philosophers using threads and mutexes.
* Each philosopher is represented by a thread.
* Mutexes are used to prevent multiple philosophers from taking the same fork at the same time.
Bonus Part
* The bonus part implements philosophers using processes and semaphores.
* All forks are represented by a semaphore.
* Each philosopher is represented by a process.
* The main process is not a philosopher.
* The bonus will only be graded if the mandatory part is perfect.
How to Compile
To compile the mandatory part:
make
To compile the bonus part:
make bonus
To clean object files:
make clean
To clean all compiled files:
make fclean
To recompile the project:
make re
How to Run
Example usage:
./philo 5 800 200 200
This command runs the program with 5 philosophers, time_to_die = 800ms, time_to_eat = 200ms, and time_to_sleep = 200ms.
With an optional stop condition:
./philo 5 800 200 200 5
Here, the simulation stops when every philosopher has eaten at least 5 times.
Resources
* Dining Philosophers Problem
* POSIX Threads
* Semaphores in C

Made with ❤️ for the 1337 curriculum.

