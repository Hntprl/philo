/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/15 18:24:01 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eat(t_philo *philo)
{
    size_t i = ft_gettime() - philo->table->start_time;
	printf("%ld %d has taken a fork\n",i , philo->id);
	printf("%ld %d is eating\n",i , 1);
	usleep(philo->table->time_to_eat);
}

void ft_sleep(t_philo *philo)
{
    size_t i = ft_gettime() - philo->table->start_time;
	printf("%ld %d is sleeping\n",i , philo->id);
	usleep(philo->table->time_to_sleep);
}

void ft_think(t_philo *philo)
{
    size_t i = ft_gettime() - philo->table->start_time;
	printf("%ld %d is thinking\n",i , philo->id);
	usleep(700);
}