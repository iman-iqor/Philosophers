#include "philo.h"
int	handle_one_philo(t_rules *rules)
{
	printf("0 1 is thinking\n");
	usleep(rules->time_to_die * 1000);
	printf("%d 1 died\n", rules->time_to_die);
	ft_gc(0, 'f');
	return (0);
}

void	ft_destroy_all(t_rules *rules)
{
	int	i;

	for (i = 0; i < rules->nb_philo; i++)
		pthread_mutex_destroy(&rules->forks[i]);
	for (i = 0; i < rules->nb_philo; i++)
		pthread_mutex_destroy(&rules->philos[i].meal_mutex);
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (is_it_null(argv, argc) || is_it_space(argv))
		return (1);
	if (!check_args(&rules, argc, argv))
		return (1);
	if (rules.nb_philo == 1)
		return (handle_one_philo(&rules));
	if (!init_simulation(&rules) || !start_simulation(&rules))
	{
		ft_gc(0, 'f');
		ft_destroy_all(&rules);
		return (1);
	}
	ft_destroy_all(&rules);
	ft_gc(0, 'f');
	return (0);
}
