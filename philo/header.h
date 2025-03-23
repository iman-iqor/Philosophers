#ifndef HEADER_H
#define HEADER_H

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
    int id;                // Philosopher's ID
    pthread_t thread;      // Thread for each philosopher
    pthread_mutex_t *left_fork;  // Pointer to left fork mutex
    pthread_mutex_t *right_fork; // Pointer to right fork mutex
    int time_to_die;       // Time before death
    int time_to_eat;       // Time spent eating
    int time_to_sleep;     // Time spent sleeping
} t_philo;

typedef struct s_data
{
    int philo_num;
    int i;
} t_data;

int	ft_atoi(const char *str);

#endif 



/*
pthread_t is a handle or identifier for a thread, and it's defined in the <pthread.h> library.
*/