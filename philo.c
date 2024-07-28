/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:01 by amarouf           #+#    #+#             */
/*   Updated: 2024/07/27 21:45:11 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

 void philo_parser(char **av)
 {
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			(write(1, "Wrong input: Only digits!", 26), exit(1));
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				(write(1, "Wrong input: Only digits!", 26), exit(1));
			j ++;
		}
		i ++;
	}
 }

void philo_born(t_philo *philo)
{
	while (philo->number_of_philosophers)
	{
		
		philo->number_of_philosophers --;
	}
}

 void philo_table(char **av)
 {
	t_philo philo;

	philo.number_of_philosophers = atoi(av[1]);
	philo.time_to_die = atoi(av[2]);
	philo.time_to_eat = atoi(av[3]);
	philo.time_to_sleep = atoi(av[4]);
	philo.eat_num = atoi(av[5]);
	philo_born(&philo);
 }

int main (int ac, char **av)
{
	if (ac == 6)
	{
		philo_parser(av);
		philo_table(av);
	}
	else
		(write(1, "Wrong input: Need 6 args", 26), exit(1));
}