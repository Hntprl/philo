/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:51:46 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/15 17:49:54 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eat(t_table *table)
{
    size_t i = ft_gettime() - table->start_time;
	printf("%ld %d has taken a fork\n",i , table->philo->id);
	printf("%ld %d is eating\n",i , 1);
	usleep(table->time_to_eat);
}

void ft_sleep(t_table *table)
{
    size_t i = ft_gettime() - table->start_time;
	printf("%ld %d is sleeping\n",i , table->philo->id);
	usleep(table->time_to_sleep);
}

void ft_think(t_table *table)
{
    size_t i = ft_gettime() - table->start_time;
	printf("%ld %d is thinking\n",i , table->philo->id);
	usleep(700);
}