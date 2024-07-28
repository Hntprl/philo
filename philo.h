/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:05 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/27 21:32:54 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
    int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_num;
}       t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif