/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:36:07 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 19:36:25 by ifadhli          ###   ########.fr       */
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

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	long long		start_time;
	int				stop;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_rules			*rules;
	int				ate;
	long long		last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	t_rules			rules;
	pthread_mutex_t	*forks;
}					t_data;

int					check_args(int ac);
int					pars_pos_int(char *str);
int					init_philosophers(t_data *data);
int					init_mutex(t_data *data);
int					init_rules(t_rules *rules, int ac, char **av);
int					start_simulation(t_data *data);
void				*routine(void *arg);
void				*monitor_routine(void *arg);
long long			get_time(void);
void				print_action(t_philo *philo, char *str);
int					get_stop(t_rules *rules);
void				set_stop(t_rules *rules);
int					start_simulation(t_data *data);

#endif
