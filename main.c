/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:03:29 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/13 21:21:05 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (check_args(ac) || init_rules(&data.rules, ac, av))
    {
        printf("Error: invalid arguments\n");
        return (1);
    }
    if (init_mutex(&data) || init_philosophers(&data))
    {
        printf("Error: init failed\n");
        return (1);
    }
    if (start_simulation(&data))
    {
        printf("Error: simulation failed\n");
        return (1);
    }
    int i = 0;
    while (i < data.rules.nb_philo)
    {
        pthread_mutex_destroy(&data.philos[i].meal_mutex);
        i++;
    }
    free(data.philos);
    free(data.forks);
    pthread_mutex_destroy(&data.rules.print_mutex);
    pthread_mutex_destroy(&data.rules.stop_mutex);

    return (0);
}
