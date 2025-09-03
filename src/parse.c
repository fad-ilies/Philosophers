/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifadhli <ifadhli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:32:55 by ifadhli           #+#    #+#             */
/*   Updated: 2025/09/03 22:55:59 by ifadhli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac)
{
	if (ac < 5)
		return (1);
	else if (ac > 6)
		return (1);
	else
		return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '-')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (1);
		i++;
	}
	return (res);
}
