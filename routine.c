/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:14:11 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 19:34:21 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "a pris la fourchette gauche");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "a pris la fourchette droite");
	print_action(philo, "mange");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_eat = get_time();
	philo->ate++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_action(philo, "est en train de dormir");
	usleep(philo->rules->time_to_sleep * 1000);
	print_action(philo, "pense");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_stop(philo->rules))
	{
		philo_eat(philo);
		if (philo->rules->nb_meal != -1 && philo->ate >= philo->rules->nb_meal)
			break ;
		philo_sleep_think(philo);
	}
	return (NULL);
}

static int	check_death(t_data *data, int i, long long *time_since_meal)
{
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	*time_since_meal = get_time() - data->philos[i].last_eat;
	if (data->rules.nb_meal != -1 && data->philos[i].ate >= data->rules.nb_meal)
	{
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if (*time_since_meal > data->rules.time_to_die)
	{
		print_action(&data->philos[i], "est mort");
		set_stop(&data->rules);
		return (-1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	int			full_count;
	long long	time_since_meal;
	int			status;

	data = (t_data *)arg;
	while (!get_stop(&data->rules))
	{
		full_count = 0;
		i = 0;
		while (i < data->rules.nb_philo)
		{
			status = check_death(data, i, &time_since_meal);
			if (status == -1)
				return (NULL);
			else if (status == 1)
				full_count++;
			i++;
		}
		if (data->rules.nb_meal != -1 && full_count == data->rules.nb_philo)
			return (set_stop(&data->rules), NULL);
		usleep(1000);
	}
	return (NULL);
}
