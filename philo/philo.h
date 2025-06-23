#ifndef PHILO_H
#define PHILO_H

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>
# include <sys/time.h>

#define NUM_PHILO 2


# define INT_MAX 2147483647
# define INT_MIN -2147483648




typedef struct s_atoi_state
{
	int i;
	long result;
	int signe;
	int tmp;
}	t_atoi_state;
struct s_rules;


typedef struct s_philo
{
	int             id;
	int             meals_eaten;
	long long       last_meal;
	pthread_t       thread;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_rules  *rules; // pointer to shared rules
} t_philo;

typedef struct s_rules
{
	int             nb_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             must_eat_count;
	long long       start_time;
	int             someone_died;

	pthread_mutex_t *forks;       // array of mutexes
	pthread_mutex_t print_mutex;  // to avoid messy output
	t_philo         *philos;
} t_rules;


typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

//********   UTILS   ********//
int	ff_atoi(char *str,int* error_flag);
void	init_vars(t_atoi_state *vars);
int is_it_alpha_error(void);
int	check_int_overflow(long number);
int	is_it_alpha(char *str, int *i);
int ft_strlen(char* str);
int	is_it_space(char **str);
int	is_it_null(char **argv, int argc);

//********   INIT   ********//
int init_simulation(t_rules *rules,int argc,char** argv);

//********  GARBAGE COLLECTER  ********//
void	* ft_gc(size_t n, char flag);
void	fr_ee(t_gc *gc);
t_gc	*create(void *ptr);
void	add(t_gc **gc, t_gc *new);


#endif 



/*
pthread_t is a handle or identifier for a thread, and it's defined in the <pthread.h> library.
*/