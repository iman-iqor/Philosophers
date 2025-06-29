#include "philo.h"

int	check_args(t_rules *rules, int argc, char **argv)
{
	int	error_flag;

	error_flag = 0;
	if (argc < 5 || argc > 6)
	{
		write(2,
			"\033[0;31mError: wrong number of arguments (should be 4 or 5 params)\n\033[0m",
			71);
		return (0);
	}
	rules->nb_philo = ff_atoi(argv[1], &error_flag);
	rules->time_to_die = ff_atoi(argv[2], &error_flag);
	rules->time_to_eat = ff_atoi(argv[3], &error_flag);
	rules->time_to_sleep = ff_atoi(argv[4], &error_flag);
	if (rules->nb_philo <= 0 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
	{
		write(2, "Error: All values must be positive integers\n", 45);
		return (0);
	}
	if (argc == 6)
	{
		rules->must_eat_count = ff_atoi(argv[5], &error_flag);
		if (rules->must_eat_count < 0)
		{
			write(2, "Error: must_eat_count must be >= 0\n", 36);
			return (0);
		}
	}
	else
	{
		rules->must_eat_count = -1;
	}
	if (error_flag)
		return (0);
	return (1);
}
int	init_rules(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = ft_gc(sizeof(pthread_mutex_t) * rules->nb_philo, 'm');
	if (!rules->forks)
		return (0);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0
		|| pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (0);
	rules->someone_died = 0;
	rules->philos = ft_gc(sizeof(t_philo) * rules->nb_philo, 'm');
	if (!rules->philos)
		return (0);
	rules->start_time = get_curr_time_ms();
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal = rules->start_time;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
		pthread_mutex_init(&rules->philos[i].meal_mutex, NULL);
		i++;
	}
	return (1);
}


int	init_simulation(t_rules *rules)
{
	// Next steps: initialize forks, philosopher data, start_time, etc
	if (!init_rules(rules))
		return (0);
	return (1);
}
int	start_simulation(t_rules *rules)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philos[i].thread, NULL, philo_routine,
				&rules->philos[i]) != 0)
		{
			write(2, "Error: failed to create the philosopher thread!", 48);
			return (0);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, the_monitor, rules) != 0)
	{
		write(2, "Error: failed to create the monitor thread", 43);
		return (0);
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}