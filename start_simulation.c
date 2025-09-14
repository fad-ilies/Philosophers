/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:14:34 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 19:34:14 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		data->philos[i].last_eat = data->rules.start_time;
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
		{
			printf("Error : mauvaise init des threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static void	join_philo_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;

	data->rules.start_time = get_time();
	if (create_philo_threads(data))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		printf("Error : mauvaise init du monitor\n");
		return (1);
	}
	pthread_join(monitor, NULL);
	join_philo_threads(data);
	return (0);
}
