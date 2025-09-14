/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:03:29 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 19:21:38 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	free(data->philos);
	free(data->forks);
	pthread_mutex_destroy(&data->rules.print_mutex);
	pthread_mutex_destroy(&data->rules.stop_mutex);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac) || init_rules(&data.rules, ac, av))
		return (printf("Error: invalid arguments\n"), 1);
	if (init_mutex(&data) || init_philosophers(&data))
		return (printf("Error: init failed\n"), 1);
	if (start_simulation(&data))
		return (printf("Error: simulation failed\n"), 1);
	cleanup(&data);
	return (0);
}
