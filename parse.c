/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:32:55 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/14 19:34:36 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pars_pos_int(char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	if (!str || !str[0])
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	if (res <= 0)
		return (-1);
	return ((int)res);
}

int	check_args(int ac)
{
	if (ac == 5 || ac == 6)
		return (0);
	return (1);
}
