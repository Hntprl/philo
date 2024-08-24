/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/24 11:37:34 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printstate(char *str, int id, size_t start_time)
{
	size_t i = ft_gettime() - start_time;
	printf("%ld %d %s", i, id, str);
}

void eat(t_philo *philo)
{
	int	death_count;
	
	if (philo->id % 2 == 0)
		usleep(700 * 1000);
	pthread_mutex_lock(philo->r_fork);
	death_count = philo->last_meal - ft_gettime();
	if (death_count > philo->table->time_to_die)
		philo->table->death = 1;
    size_t i = ft_gettime() - philo->table->start_time;
	philo->last_meal = i;
	ft_printstate("has taken a fork\n", philo->id, philo->table->start_time);
	pthread_mutex_lock(philo->l_fork);
	ft_printstate("has taken a fork\n", philo->id, philo->table->start_time);
	ft_printstate("is eating\n", philo->id, philo->table->start_time);
	usleep(philo->table->time_to_eat * 1000);
	philo->eat_num += 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void ft_sleep(t_philo *philo)
{
	ft_printstate("is sleeping\n", philo->id, philo->table->start_time);
	usleep(philo->table->time_to_sleep * 1000);
}

void ft_think(t_philo *philo)
{
	ft_printstate("is thinking\n", philo->id, philo->table->start_time);
	usleep(700);
}