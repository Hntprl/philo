/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/20 20:42:02 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(7000);
    size_t i = ft_gettime() - philo->table->start_time;
	philo->l_fork = &philo->table->forks[philo->id + 1];
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n",i , philo->id);
	philo->r_fork = &philo->table->forks[philo->id % philo->table->number_of_philosophers];
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n",i , philo->id);
	pthread_mutex_lock(&philo->table->eat_mutex);
	printf("%ld %d is eating\n",i , philo->id);
	usleep(philo->table->time_to_eat * 1000);
	philo->eat_num += 1;
	pthread_mutex_unlock(&philo->table->eat_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void ft_sleep(t_philo *philo)
{
    size_t i = ft_gettime() - philo->table->start_time;
	printf("%ld %d is sleeping\n",i , philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

void ft_think(t_philo *philo)
{
    size_t i = ft_gettime() - philo->table->start_time;
	printf("%ld %d is thinking\n",i , philo->id);
	usleep(700);
}