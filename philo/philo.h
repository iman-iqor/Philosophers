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
	pthread_mutex_t death_mutex;
	t_philo         *philos;
} t_rules;


typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

//********  GARBAGE COLLECTER  ********//
void	* ft_gc(size_t n, char flag);
void	fr_ee(t_gc *gc);
t_gc	*create(void *ptr);
void	add(t_gc **gc, t_gc *new);
/********** MONITOR **********/
void	*the_monitor(void *arg);
int		check_meals(t_rules *rules);
int		check_death(t_rules *rules, int i);
/********** ROUTINE **********/
void	*philo_routine(void *arg);
void	print_status(t_philo *philo, char *status);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
int		someone_is_dead(t_philo *philo);
/********** TIME **********/
long long	get_curr_time_ms(void);
void		philo_sleep(t_philo *philo, long long duration);
/********** INIT **********/
int		check_args(t_rules *rules, int argc, char **argv);
int		init_rules(t_rules *rules);
int		init_simulation(t_rules *rules);
int		start_simulation(t_rules *rules);
/********** UTILS **********/
int		is_it_null(char **argv, int argc);
int		is_it_space(char **str);
int		is_it_alpha(char *str, int *i);
int		is_it_alpha_error(void);
int		check_int_overflow(long number);
int		ff_atoi(char *str, int *error_flag);
int		ft_strlen(char *str);
void	init_vars(t_atoi_state *vars);

#endif 



/*
pthread_t is a handle or identifier for a thread, and it's defined in the <pthread.h> library.
*/