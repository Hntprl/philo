/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:05:43 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/19 01:55:20 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	a;

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
	return (a * s);
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

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		n --;
		c1 ++;
		c2 ++;
	}
	return (0);
}

int	philo_parser(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			return (write(1, "Wrong input!\n", 13), 1);
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (write(1, "Wrong input!\n", 13), 1);
			j ++;
		}
		i ++;
	}
	return (0);
}
