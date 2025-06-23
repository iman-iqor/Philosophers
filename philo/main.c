#include "philo.h"

int	handle_one_philo(t_rules *rules)
{
	printf("0 1 is thinking\n");
	usleep(rules->time_to_die * 1000);
	printf("%d 1 died\n", rules->time_to_die);
	ft_gc(0, 'f');
	return (0);
}
int	check_args(t_rules *rules, int argc, char **argv)
{
	int	error_flag;

	error_flag = 0;
	if (argc < 5 || argc > 6)
	{
		write(2,
			"\033[0;31mError: wrong number of arguments (should be 4 or 5 params)\n\033[0m",
			71);
		exit(0);
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


long long	get_curr_time_ms(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return ((time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000));
}
int	init_rules(t_rules *rules, int argc, char **argv)
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
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (0);
	rules->philos = ft_gc(sizeof(pthread_mutex_t) * rules->nb_philo, 'm');
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
}
int	init_simulation(t_rules *rules, int argc, char **argv)
{
	// Next steps: initialize forks, philosopher data, start_time, etc
	init_rules(rules, argc, argv);
	return (1);
}
// ff_atoi********************************
int	is_it_space(char **str)
{
	int	i;
	int	len;
	int	check;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		check = 0;
		len = ft_strlen(str[i]);
		while (str[i][j])
		{
			if (str[i][j] == ' ')
				check++;
			j++;
		}
		if (check == len)
		{
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	return (0);
}
int	is_it_null(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i][0])
		{
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	return (0);
}
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_it_alpha(char *str, int *i)
{
	if (!str[*i])
		return (1);
	while (str[*i])
	{
		if (!(((str[*i] >= '0' && str[*i] <= '9'))))
		{
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	check_int_overflow(long number)
{
	if (number > INT_MAX || number < INT_MIN)
	{
		write(2, "Error: int overflow\n", 20);
		ft_gc(0, 'f');
		return (1);
	}
	return (0);
}

int	is_it_alpha_error(void)
{
	write(2, "error: alpha forbiden", 22);
	ft_gc(0, 'f');
	return (1);
}

void	init_vars(t_atoi_state *vars)
{
	vars->i = 0;
	vars->result = 0;
	vars->signe = 1;
}

int	ff_atoi(char *str, int *error_flag)
{
	t_atoi_state	vars;

	init_vars(&vars);
	while (str[vars.i] == '\t' || str[vars.i] == '\n' || str[vars.i] == '\v'
		|| str[vars.i] == '\f' || str[vars.i] == '\r' || str[vars.i] == ' ')
		vars.i++;
	vars.i = 0;
	if (str[vars.i] == '-' || str[vars.i] == '+')
	{
		if (str[vars.i] == '-')
			vars.signe = -1;
		vars.i++;
	}
	vars.tmp = vars.i;
	if (is_it_alpha(str, &vars.i) || !(str[vars.tmp] >= '0'
			&& str[vars.tmp] <= '9'))
		is_it_alpha_error();
	while (str[vars.tmp] >= '0' && str[vars.tmp] <= '9')
	{
		vars.result = vars.result * 10 + str[vars.tmp] - 48;
		if (check_int_overflow(vars.result * vars.signe))
			*error_flag = 1;
		vars.tmp++;
	}
	return ((int)(vars.result * vars.signe));
}
//*********************** */
int	main(int argc, char **argv)
{
	t_rules	rules;

	if (is_it_null(argv, argc) || is_it_space(argv))
		return (1);
	if (!check_args(&rules, argc, argv))
		return (1);
	if (rules.nb_philo == 1)
		return (handle_one_philo(&rules));
	if (!init_simulation(&rules, argc, argv))
		return (1);
	ft_gc(0, 'f');
	return (0);
}
