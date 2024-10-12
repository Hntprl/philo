/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:49:53 by amarouf           #+#    #+#             */
/*   Updated: 2024/10/08 19:53:36 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printstate(char *str, t_philo *philo)
{
	size_t	i;

	pthread_mutex_lock(&philo->table->print);
	i = ft_gettime() - philo->start_time;
	printf("%ld %d %s", i, philo->id, str);
	if (ft_memcmp("died", str, 4))
		pthread_mutex_unlock(&philo->table->print);
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

int	mutex_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		i ++;
	}
	if (pthread_mutex_init(&table->print, NULL)
		|| pthread_mutex_init(&table->death_mutex, NULL)
		|| pthread_mutex_init(&table->eat_mutex, NULL))
		return (1);
	return (0);
}

int	death_check(t_philo *philo, int i, int death_count)
{
	if (death_count >= philo[i].table->time_to_die)
	{
		if (philo->table->eat_num != -1)
		{
			if (philo[i].eat_num < philo[i].table->eat_num)
				return (ft_printstate("died\n", &philo[i]), 1);
		}
		else
			return (ft_printstate("died\n", &philo[i]), 1);
	}
	return (0);
}

void	*monitor(void *data)
{
	int		death_count;
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		i = -1;
		while (++ i < philo->table->philo_num)
		{
			pthread_mutex_lock(&philo->table->death_mutex);
			death_count = ft_gettime() - philo[i].last_meal;
			pthread_mutex_unlock(&philo->table->death_mutex);
			pthread_mutex_lock(&philo->table->eat_mutex);
			if (death_check(philo, i, death_count))
				return (NULL);
			if (philo->table->eat == philo->table->philo_num)
				return (pthread_mutex_unlock(&philo->table->eat_mutex), NULL);
			pthread_mutex_unlock(&philo->table->eat_mutex);
		}
	}
	return (NULL);
}
