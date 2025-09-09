/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:00:30 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/09 18:45:09 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_data *data)
{
	int	i;

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
		data->philos[i].right_fork = &data->forks[(i + 1)
			% data->rules.nb_philo]; //
			% pour que le dernier r4eprenne la fourchette du premier;
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->rules.nb_philo);
	if (!data->forks)
		return (1);
	while (i < data->rules.nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_rules(t_rules *rules, int ac, char **av)
{
	rules->nb_philo = pars_pos_int(av[1]);
	rules->time_to_die = pars_pos_int(av[2]);
	rules->time_to_eat = pars_pos_int(av[3]);
	rules->time_to_sleep = pars_pos_int(av[4]);
	if (ac == 6)
		rules->nb_meal = pars_pos_int(av[5]);
	else
		rules->nb_meal = -1;
	if (rules->nb_philo == -1 || rules->time_to_die == -1
		|| rules->time_to_eat == -1 || rules->time_to_sleep == -1 || (ac == 6
			&& rules->nb_meal == -1))
		return (1);
	return (0);
}