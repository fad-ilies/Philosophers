/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:57:18 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/09 20:03:55 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_data *data)
{
    int i;

    i = 0;
    while (i < data->rules.nb_philo)
    {
        if (pthread_create(&data->philos[i].thread), NULL, routine, &data->philos[i] != 0)
        {
            printf("Error : Mauvaise init des thread\n");
            return (1);
        }
        i++;
    }
    return (0);
}