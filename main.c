/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:03:29 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/09 18:55:14 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data data;
	
	if (check_args(ac))
	{
		printf("Error : mauvais nb d'arguments\n");
		return (1);
	}
	if (init_rules(&data, ac, av))
	{
		printf("Error : Argument invalide\n");
		return (1);
	}
	if (init_mutex(&data))
	{
		printf("Error : Mauvaise init des mutex\n");
		return (1);
	}
	if (init_philosophers(&data))
	{
		printf("Error : Mauvaise init des philos\n");
		return (1);
	}
	return (0);
}
