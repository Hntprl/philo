/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:05 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/10 23:14:17 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_table
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_num;
}	t_table;

typedef struct s_philo
{
	int id;
	pthread_t *ph;
	t_table *table;
}       t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif