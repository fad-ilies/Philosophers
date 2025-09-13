/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:14:11 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/13 21:21:38 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

static int	get_stop(t_rules *rules)
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

static void	set_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_mutex);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->stop_mutex);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    // Petit décalage pour éviter les collisions
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!get_stop(philo->rules))
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "a pris la fourchette gauche");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "a pris la fourchette droite");

        // Manger
        print_action(philo, "mange");
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_eat = get_time();   // ✅ mise à jour protégée
        philo->ate++;                   // ✅ incrémentation du compteur
        pthread_mutex_unlock(&philo->meal_mutex);
        usleep(philo->rules->time_to_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Vérification du nombre de repas
        if (philo->rules->nb_meal != -1 && philo->ate >= philo->rules->nb_meal)
            break; // ✅ Philosophe a fini de manger

        // Dormir
        print_action(philo, "est en train de dormir");
        usleep(philo->rules->time_to_sleep * 1000);

        // Penser
        print_action(philo, "pense");
        usleep(100); // ✅ petit délai pour éviter les boucles trop rapides
    }
    return (NULL);
}

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	/* small stagger to reduce collisions */
// 	if (philo->id % 2 == 0)
// 		usleep(1000);
// 	while (!get_stop(philo->rules))
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, "a pris la fourchette gauche");
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, "a pris la fourchette droite");
// 		/* manger */
// 		print_action(philo, "mange");
// 		pthread_mutex_lock(&philo->meal_mutex);
// 		philo->last_eat = get_time();
// 		pthread_mutex_unlock(&philo->meal_mutex);
// 		philo->last_eat = get_time();
// 		philo->ate++;
// 		usleep(philo->rules->time_to_eat * 1000);
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);
// 		/* dormir */
// 		print_action(philo, "est en train de dormir");
// 		usleep(philo->rules->time_to_sleep * 1000);
// 		print_action(philo, "pense");
// 	}
// 	return (NULL);
// }

// void	*monitor_routine(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)arg;
// 	while (!get_stop(&data->rules))
// 	{
// 		i = 0;
// 		while (i < data->rules.nb_philo)
// 		{
// 			if (get_time() - data->philos[i].last_eat > data->rules.time_to_die)
// 			{
// 				print_action(&data->philos[i], "est mort");
// 				set_stop(&data->rules);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		usleep(1000); /* vérification légère toutes les 1ms */
// 	}
// 	return (NULL);
// }

void    *monitor_routine(void *arg)
{
    t_data      *data;
    int         i;
    int         full_count;
    long long   time_since_meal;

    data = (t_data *)arg;
    while (!get_stop(&data->rules))
    {
        full_count = 0;
        i = 0;
        while (i < data->rules.nb_philo)
        {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            time_since_meal = get_time() - data->philos[i].last_eat;
            if (data->rules.nb_meal != -1 && data->philos[i].ate >= data->rules.nb_meal)
                full_count++;
            pthread_mutex_unlock(&data->philos[i].meal_mutex);

            if (time_since_meal > data->rules.time_to_die)
            {
                print_action(&data->philos[i], "est mort");
                set_stop(&data->rules);
                return (NULL);
            }
            i++;
        }
        if (data->rules.nb_meal != -1 && full_count == data->rules.nb_philo)
        {
            set_stop(&data->rules); // ✅ tous les philosophes ont fini
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

int	start_simulation(t_data *data)
{
	int i;
	pthread_t monitor;

	data->rules.start_time = get_time();
	i = 0;
	while (i < data->rules.nb_philo)
	{
		data->philos[i].last_eat = data->rules.start_time;
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
		{
			printf("Error : mauvaise init des threads\n");
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		printf("Error : mauvaise init du monitor\n");
		return (1);
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->rules.nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
