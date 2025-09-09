/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:04:22 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/09 20:04:17 by ifadhli          ###   ########.fr       */
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
	int nb_meal;                 /* -1 si pas précisé */
	long long start_time;        /* moment où la simulation commence */
	pthread_mutex_t print_mutex; /* pour sérialiser l'affichage */

}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_rules *rules;             /* pointeur vers les règles globales */
	int ate;                    /* nombre de fois mangé (utilisé plus tard) */
	long long last_eat;         /* timestamp ms du dernier repas */
	pthread_mutex_t *left_fork; /* pointeurs vers les fourchettes (mutex) */
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	t_rules			rules;
	pthread_mutex_t *forks; /* tableau de mutex (nb_philo elements) */
}					t_data;

int					check_args(int ac);
int					pars_pos_int(char *str);
int					init_philosophers(t_data *data);
int					init_mutex(t_data *data);
int					init_rules(t_rules *rules, int ac, char **av);
int					start_simulation(t_data *data);
void				*routine(void *arg);

#endif /* PHILO_H */
