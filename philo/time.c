#include"philo.h"


long long	get_curr_time_ms(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return ((time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000));
}
void	philo_sleep(t_philo *philo, long long duration)
{
	long long	start_time;

	start_time = get_curr_time_ms();
	while ((get_curr_time_ms() - start_time < duration) && !someone_is_dead(philo))
		usleep(50);
}