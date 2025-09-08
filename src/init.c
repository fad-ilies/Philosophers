/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:00:30 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/08 23:25:08 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_data *data)
{
	int i;

	i = 0;
    data->philos = malloc(sizeof(t_philo) * data->rules.nb_philo);
    if (!data->philos)
        return (1);
    while (i < data->rules.nb_philo)
    {
        data->philos[i].id = i + 1;
        data->philos[i].rules = &data->rules;
        data->philos[i].ate = 0;
        data->philos[i].last_eat = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->rules.nb_philo]; // % pour que le dernier r4eprenne la fourchette du premier;
        i++;
    }
    return (0);
}