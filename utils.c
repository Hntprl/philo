/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:05:43 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/23 22:21:54 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

int	check_overflow(char *str, long long nbr)
{
	if (ft_strlen(str) > 19 || nbr > 2147483647)
		return (-1337);
	else
		return ((int)nbr);
}

int	ft_atoi(char *str)
{
	int			i;
	int			s;
	long long	a;

	s = 1;
	i = 0;
	a = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i ++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		a = (str[i] - '0') + (a * 10);
		i ++;
	}
	return (check_overflow(str, a * s));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_gettime(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}
