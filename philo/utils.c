#include"philo.h"

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
