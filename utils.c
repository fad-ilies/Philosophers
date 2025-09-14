/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:41:55 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 18:59:07 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int	get_stop(t_rules *rules)
{
	int	val;

	pthread_mutex_lock(&rules->stop_mutex);
	val = rules->stop;
	pthread_mutex_unlock(&rules->stop_mutex);
	return (val);
}

void	print_action(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->rules->print_mutex);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	set_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_mutex);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->stop_mutex);
}
