/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:04:22 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/03 23:00:20 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// typedef struct s_philo
// {
// 	int				id;
// 	int				ate;
// 	long			last_eat;
// 	pthread_t		pid;
// 	int				nb_meals;
// 	pthread_mutex_t	*fork;
// }					t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_rules			rules;
	pthread_mutex_t	*fork;
	pthread_mutex_t	fork_right;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_rules			rules;
} t_data

#endif