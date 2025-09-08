/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:03:29 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/08 18:33:52 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// int main (int ac, char **av)
// {
//     t_philo main;

//     n philo -> nthread
//     loop -> cree n philo
    
//     while (1)
//     {
//         if (!monitor())
//             return 0;
//     }
    
// }

// main test //

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (check_args(ac))
		return (printf("Error: wrong number of arguments\n"), 1);
	if (init_rules(&data.rules, ac, av))
		return (printf("Error: init rules failed\n"), 1);
	if (init_philos(&data))
		return (printf("Error: init philos failed\n"), 1);

	// Création des threads
	i = 0;
	while (i < data.rules.nb_philo)
	{
		pthread_create(&data.philo[i].thread, NULL, philo_routine, &data.philo[i]);
		i++;
	}
	// Join des threads (attente)
	i = 0;
	while (i < data.rules.nb_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
}
