/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:05:43 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/27 21:06:57 by amarouf          ###   ########.fr       */
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
