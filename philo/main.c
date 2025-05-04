#include "philo.h"


void init_simulation(t_rules *rules,int argc,char** argv)
{
    if(!(argc==5))
    {
        write(2, "\033[0;31mwrong arguments! there should be 5 arguments!\033[0m\n",58);
        exit(1);
    }
    else
    {
        
        rules->nb_philo= ff_atoi(argv[1]);
        rules->time_to_die=ff_atoi(argv[2]);
        rules->time_to_eat=ff_atoi(argv[3]);
        rules->time_to_sleep=ff_atoi(argv[4]);
        if (rules->nb_philo <= 0 || rules->time_to_die <= 0 || rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
        {
            write(2, "Error: All values must be positive integers\n", 44);
            exit(1);
        }
    }
}

int main(int argc,char** argv)
{
    
    t_rules rules;
    is_it_null(argv,argc);
    is_it_space(argv);
    init_simulation(&rules,argc,argv);
    

}
