#include "philo.h"

int check_args(t_rules *rules,int argc,char** argv)
{
    if (argc < 5 || argc > 6)
    {
        write(2, "\033[0;31mError: wrong number of arguments (should be 4 or 5 params)\n\033[0m", 75);
        exit(0);
    }
    rules->nb_philo     = ff_atoi(argv[1]);
    rules->time_to_die  = ff_atoi(argv[2]);
    rules->time_to_eat  = ff_atoi(argv[3]);
    rules->time_to_sleep= ff_atoi(argv[4]);

    if (rules->nb_philo <= 0 || rules->time_to_die <= 0
        || rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
    {
        write(2, "Error: All values must be positive integers\n", 44);
        return(0);
    }
    if (argc == 6)
    {
        rules->must_eat_count = ff_atoi(argv[5]);
        if (rules->must_eat_count < 0)
        {
            write(2, "Error: must_eat_count must be >= 0\n", 33);
            return(0);
        }
    }
    else
    {
        rules->must_eat_count = -1; 
    }
    return 1;
}

int init_rules(t_rules * rules,int argc ,char** argv)
{

}
int init_simulation(t_rules *rules,int argc,char** argv)
{

    check_args(rules,argc,argv);
    // Next steps: initialize forks, philosopher data, start_time, etc
    init_rules(rules,argc,argv);
    return 1;
}