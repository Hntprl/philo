/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/23 22:21:59 by amarouf          ###   ########.fr       */
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

void	ft_printstate(char *str, t_philo *philo)
{
	size_t	i;

	pthread_mutex_lock(&philo->table->print);
	i = ft_gettime() - philo->start_time;
	printf("%ld %d %s", i, philo->id, str);
	if (ft_memcmp("died", str, 4))
		pthread_mutex_unlock(&philo->table->print);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(700);
	pthread_mutex_lock(philo->r_fork);
	ft_printstate("has taken a fork\n", philo);
	pthread_mutex_lock(philo->l_fork);
	ft_printstate("has taken a fork\n", philo);
	ft_printstate("is eating\n", philo);
	pthread_mutex_lock(&philo->table->eat_mutex);
	philo->eat_num += 1;
	pthread_mutex_unlock(&philo->table->eat_mutex);
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal = ft_gettime();
	pthread_mutex_unlock(&philo->table->death_mutex);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleep_think(t_philo *philo)
{
	ft_printstate("is sleeping\n", philo);
	usleep(philo->table->time_to_sleep * 1000);
	ft_printstate("is thinking\n", philo);
}
