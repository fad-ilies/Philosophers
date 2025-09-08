/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:04:22 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/08 22:42:21 by ifadhli          ###   ########.fr       */
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
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_meal;        /* -1 si pas précisé */
}   t_rules;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    t_rules         *rules;         /* pointeur vers les règles globales */
    int             ate;            /* nombre de fois mangé (utilisé plus tard) */
    long long       last_eat;       /* timestamp ms du dernier repas */
    pthread_mutex_t *left_fork;     /* pointeurs vers les fourchettes (mutex) */
    pthread_mutex_t *right_fork;
}   t_philo;

typedef struct s_data
{
    t_philo     *philos;
    t_rules     rules;
    pthread_mutex_t *forks;         /* tableau de mutex (nb_philo elements) */
    pthread_mutex_t print_mutex;    /* pour sérialiser l'affichage */
}   t_data;

#endif /* PHILO_H */
