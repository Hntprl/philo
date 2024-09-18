/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/18 06:04:13 by amarouf          ###   ########.fr       */
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

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(700);
	pthread_mutex_lock(philo->r_fork);
	ft_printstate("has taken a rfork\n", philo);
	pthread_mutex_lock(philo->l_fork);
	ft_printstate("has taken a lfork\n", philo);
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
