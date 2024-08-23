/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/23 10:54:18 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eat(t_philo *philo)
{
	int death_count;

	if (philo->id % 2 == 0)
		usleep(700 * 1000);
	pthread_mutex_lock(&philo->table->eat_mutex);
	death_count = philo->eat_start - ft_gettime();
	if (death_count > philo->table->time_to_die)
		philo->table->death = 1;
    size_t i = ft_gettime() - philo->table->start_time;
	philo->eat_start = i;
	philo->l_fork = &philo->table->forks[philo->id + 1];
	pthread_mutex_lock(philo->l_fork);
	printf("%ld %d has taken a fork\n",i , philo->id);
	philo->r_fork = &philo->table->forks[philo->id % philo->table->number_of_philosophers];
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %d has taken a fork\n",i , philo->id);
	printf("%ld %d is eating\n",i , philo->id);
	usleep(philo->table->time_to_eat * 1000);
	philo->eat_num += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->table->eat_mutex);
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