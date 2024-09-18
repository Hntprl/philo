/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:49:53 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/18 06:06:49 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*rotune(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->table->eat_mutex);
		if (philo->table->eat_num != -1
			&& philo->table->eat_num == philo->eat_num)
			return (NULL);
		pthread_mutex_unlock(&philo->table->eat_mutex);
		eat(philo);
		ft_sleep_think(philo);
	}
	return (NULL);
}

void	mutex_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i ++;
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->eat_mutex, NULL);
}

void	*monitor(void *data)
{
	int		death_count;
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		i = 0;
		while (i < philo->table->philo_num)
		{
			pthread_mutex_lock(&philo->table->death_mutex);
			death_count = ft_gettime() - philo[i].last_meal;
			pthread_mutex_unlock(&philo->table->death_mutex);
			if (death_count >= philo[i].table->time_to_die)
				return (ft_printstate("died\n", &philo[i]), NULL);
			pthread_mutex_lock(&philo->table->eat_mutex);
			if (philo->eat_num == philo->table->eat_num)
				return (pthread_mutex_unlock(&philo->table->eat_mutex), NULL);
			pthread_mutex_unlock(&philo->table->eat_mutex);
			i ++;
		}
	}
	return (NULL);
}
