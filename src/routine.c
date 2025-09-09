/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:14:11 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/09 20:02:32 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}
void        print_action(t_philo *philo, char *str)
{
    long time;
    
    pthread_mutex_lock(&philo->rules->print_mutex);
    time = get_time() - philo->rules->start_time;
    printf("%lld %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(&philo->rules->print_mutex);
}


void    *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "a prit la fourchette de gauche");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "a prit la fourchette de droite");
        print_action(philo, "mange");
        philo->last_eat = get_time();
        philo->ate++;
        usleep(philo->rules->time_to_eat * 1000);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        print_action(philo, "est entrain de dormir");
        usleep(philo->rules->time_to_sleep * 1000);
        print_action(philo, "pense");
    }
    return (NULL);
}
