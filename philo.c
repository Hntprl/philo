/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:01 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/10 23:29:23 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mail = 0;

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

void eat(t_philo *ph)
{
	int i = 0;
	printf("Philosopher %d is eating\n", 1);
	while (i < ph->table->eat_num)
	{
		i++;
	}
}

void ft_sleep(t_philo *ph)
{
	int i = 0;
	printf("Philosopher %d is sleeping\n", 1);
	while (i < ph->table->time_to_sleep)
	{
		i++;
	}
}

void ft_think(t_philo *ph)
{
	(void)ph;
	printf("Philosopher %d is thinking\n", 1);
}

void	*rotune(void *th)
{
	t_philo *ph = (t_philo*)th;
	eat(ph);
	ft_sleep(ph);
	ft_think(ph);
	return (NULL);
}

void philo_born(t_philo *philo)
{
	philo->ph = malloc(sizeof(pthread_t));
	pthread_create(philo->ph, NULL, &rotune, philo);
	pthread_join(*(philo->ph), NULL);
}

 void philo_table(char **av)
 {
	t_table *table;
	t_philo philo;

	table = malloc(sizeof(table));
	philo.table = table;
	table->number_of_philosophers = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->eat_num = atoi(av[5]);
	if (table->number_of_philosophers > 200)
		(write(1, "Wrong input: Wrong Number!\n", 28), exit(1));
	if (table->number_of_philosophers <= 0 || table->time_to_die <= 0
	|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		(write(1, "Wrong input: Wrong Number!\n", 28), exit(1));
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
		(write(1, "Wrong input: Need 6 or 5 args\n", 31), exit(1));
	return (0);
}