/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/15 20:18:23 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printstate(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	size_t i = ft_gettime() - philo->start_time;
	printf("%ld %d %s", i, philo->id, str);
	if (ft_memcmp("died", str, 4))
		pthread_mutex_unlock(&philo->table->print);
}

void eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(700);
	pthread_mutex_lock(philo->r_fork);
	ft_printstate("has taken a fork\n", philo);
	pthread_mutex_lock(philo->l_fork);
	ft_printstate("has taken a fork\n", philo);
	ft_printstate("is eating\n", philo);
	philo->last_meal = ft_gettime();
	philo->eat_num += 1;
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void ft_sleep(t_philo *philo)
{
	ft_printstate("is sleeping\n", philo);
	usleep(philo->table->time_to_sleep * 1000);
}

void ft_think(t_philo *philo)
{
	ft_printstate("is thinking\n", philo);
	usleep(700);
}