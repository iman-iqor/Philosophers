#include "philo.h"

int check_meals(t_rules *rules)
{
	int i;
	int meals_count;
	meals_count  = 0;
	i = 0;

	if(rules->must_eat_count==0)
		return 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philos[i].meal_mutex);
		if (rules->philos[i].meals_eaten >= rules->must_eat_count)
			meals_count++;
		pthread_mutex_unlock(&rules->philos[i].meal_mutex);
		i++;
	}
	if (meals_count == rules->nb_philo)
	{
		pthread_mutex_lock(&rules->print_mutex);
		pthread_mutex_lock(&rules->death_mutex);
		rules->someone_died = 1;
		printf("all philosophers have finished their meals\n");
		pthread_mutex_unlock(&rules->death_mutex);
		pthread_mutex_unlock(&rules->print_mutex);
		return (1);
	}
	return (0);

}
int check_death(t_rules* rules , int i)
{
	long long last_meal;
	long long current_time;
	long long timestamp;

	pthread_mutex_lock(&rules->philos[i].meal_mutex);
	last_meal = rules->philos[i].last_meal;
	pthread_mutex_unlock(&rules->philos[i].meal_mutex);
	current_time = get_curr_time_ms();
	if((current_time - last_meal) >= rules->time_to_die)
	{
		pthread_mutex_lock(&rules->death_mutex);
		if(rules->someone_died)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			return 1;
		}
		rules->someone_died=1;
		timestamp= current_time - rules->philos[i].last_meal;
		printf("%lld %d died\n", timestamp, rules->philos[i].id);
		pthread_mutex_unlock(&rules->death_mutex);
		return 1;
	}
	return 0;
}
void* the_monitor(void *arg)
{
	int i;
	t_rules *rules;
	rules = (t_rules*) arg;
	while(1)
	{
		i  = 0;
		if(check_meals(rules))
			return NULL;
		while(i < rules->nb_philo)
		{
			if(check_death(rules,i))
				return NULL;
			i++;
			usleep(1000);
		}
	}
	return NULL;
}