/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:14:11 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 20:16:30 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *p)
{
	if (get_stop(p->rules))
		return ;
	pthread_mutex_lock(p->left_fork);
	if (get_stop(p->rules))
		return ((void)pthread_mutex_unlock(p->left_fork));
	print_action(p, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	if (get_stop(p->rules))
		return ((void)(pthread_mutex_unlock(p->right_fork),
			pthread_mutex_unlock(p->left_fork)));
	print_action(p, "has taken a fork");
	print_action(p, "is eating");
	pthread_mutex_lock(&p->meal_mutex);
	p->last_eat = get_time();
	p->ate++;
	pthread_mutex_unlock(&p->meal_mutex);
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

static void	philo_sleep_think(t_philo *p)
{
	if (get_stop(p->rules))
		return ;
	print_action(p, "is sleeping");
	usleep(p->rules->time_to_sleep * 1000);
	if (get_stop(p->rules))
		return ;
	print_action(p, "is thinking");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->rules->nb_philo == 1)
	{
		pthread_mutex_lock(p->left_fork);
		print_action(p, "has taken a fork");
		usleep(p->rules->time_to_die * 1000);
		print_action(p, "died");
		set_stop(p->rules);
		pthread_mutex_unlock(p->left_fork);
		return (NULL);
	}
	if (p->id % 2 == 0)
		usleep(1000);
	while (!get_stop(p->rules))
	{
		philo_eat(p);
		if (get_stop(p->rules))
			break ;
		if (p->rules->nb_meal != -1 && p->ate >= p->rules->nb_meal)
			break ;
		philo_sleep_think(p);
	}
	return (NULL);
}

static int	check_death(t_data *d, int i, long long *t)
{
	pthread_mutex_lock(&d->philos[i].meal_mutex);
	*t = get_time() - d->philos[i].last_eat;
	if (d->rules.nb_meal != -1 && d->philos[i].ate >= d->rules.nb_meal)
		return (pthread_mutex_unlock(&d->philos[i].meal_mutex), 1);
	pthread_mutex_unlock(&d->philos[i].meal_mutex);
	if (*t > d->rules.time_to_die)
	{
		print_action(&d->philos[i], "died");
		set_stop(&d->rules);
		return (-1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data		*d;
	long long	t;
	int			i;
	int			full;
	int			status;

	d = (t_data *)arg;
	while (!get_stop(&d->rules))
	{
		i = 0;
		full = 0;
		while (i < d->rules.nb_philo)
		{
			status = check_death(d, i, &t);
			if (status == -1)
				return (NULL);
			if (status == 1)
				full++;
			i++;
		}
		if (d->rules.nb_meal != -1 && full == d->rules.nb_philo)
			return (set_stop(&d->rules), NULL);
		usleep(1000);
	}
	return (NULL);
}
