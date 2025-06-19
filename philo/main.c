#include "philo.h"
int	handle_one_philo(t_rules *rules)
{
	printf("0 1 is thinking\n");
	usleep(rules->time_to_die * 1000);
	printf("%d 1 died\n", rules->time_to_die);
    ft_gc(0, 'f');
	return (0);
}
int	main(int argc, char **argv)
{
	t_rules	rules;

	is_it_null(argv, argc);
	is_it_space(argv);
	if(!init_simulation(&rules, argc, argv))
		return 1;
	if (rules.nb_philo == 1)
		return (handle_one_philo(&rules));

    ft_gc(0, 'f');
    return (0);
}
