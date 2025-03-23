#include"header.h"

int ft_atoi(const char *str)
{
    int i;
    int signe;
    int result;

    i = 0;
    signe = 0;
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
    if (str[i] == '-' || str[i] == '+')
        if (str[i++] == '-')
            signe += 1;
    result = 0;
    while (str[i] >= '0' && str[i] <= '9')
        result = result * 10 + str[i++] - 48;
    if (signe % 2 == 0)
        return (result);
    return (-result);
}
