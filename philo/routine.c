#include"philo.h"

/*
check if dead
think
pick forks
eat
sleep
repeat
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (someone_is_dead(philo))
			return (NULL);
		print_status(philo, "is thinking");
		take_forks(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_curr_time_ms();
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo_sleep(philo, philo->rules->time_to_eat);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		release_forks(philo);
		if(someone_is_dead(philo))
			return NULL;
		print_status(philo,"is sleeping");
		philo_sleep(philo,philo->rules->time_to_sleep);
	}
	return NULL;
}
void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (someone_is_dead(philo))
	{
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return ;
	}
	time = get_curr_time_ms() - philo->rules->start_time;
	printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	take_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->rules->nb_philo;
	if (philo->id % 2 != 0)
		usleep(100);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->rules->forks[right_fork]);
		pthread_mutex_lock(&philo->rules->forks[left_fork]);

	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[left_fork]);
		pthread_mutex_lock(&philo->rules->forks[right_fork]);
	}
}
void release_forks(t_philo *philo)
{
	int left_fork;
	int right_fork;
	left_fork= philo->id -1;
	right_fork = philo->id % philo->rules->nb_philo;
	if(philo->id % 2 ==0)
	{
		pthread_mutex_unlock(&philo->rules->forks[right_fork]);
		pthread_mutex_unlock(&philo->rules->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->forks[left_fork]);
		pthread_mutex_unlock(&philo->rules->forks[right_fork]);
	}
	if(philo->id%2 == 0)
		usleep(200);

}

int	someone_is_dead(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->rules->death_mutex);
	is_dead = philo->rules->someone_died;
	pthread_mutex_unlock(&philo->rules->death_mutex);
	return (is_dead);
}