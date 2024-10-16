/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/10 16:54:56 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*rotune(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->table->eat_mutex);
		if (philo->table->eat_num != -1
			&& philo->table->eat_num == philo->eat_num)
		{
			if (philo->table->eat_num != -1)
				philo->table->eat += 1;
			return (pthread_mutex_unlock(&philo->table->eat_mutex), NULL);
		}
		pthread_mutex_unlock(&philo->table->eat_mutex);
		eat(philo);
		ft_sleep_think(philo);
	}
	return (NULL);
}

void	ft_unlock_mutex(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_printstate("has taken a fork\n", philo);
		pthread_mutex_lock(philo->r_fork);
		ft_printstate("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_printstate("has taken a fork\n", philo);
		pthread_mutex_lock(philo->l_fork);
		ft_printstate("has taken a fork\n", philo);
	}
	ft_printstate("is eating\n", philo);
	pthread_mutex_lock(&philo->table->eat_mutex);
	philo->eat_num += 1;
	pthread_mutex_unlock(&philo->table->eat_mutex);
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal = ft_gettime();
	pthread_mutex_unlock(&philo->table->death_mutex);
	usleep(philo->table->time_to_eat * 1000);
	ft_unlock_mutex(philo);
}

void	ft_sleep_think(t_philo *philo)
{
	ft_printstate("is sleeping\n", philo);
	usleep(philo->table->time_to_sleep * 1000);
	ft_printstate("is thinking\n", philo);
}
