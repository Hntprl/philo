/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:01 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/15 17:48:55 by amarouf          ###   ########.fr       */
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

void	*rotune(void *data)
{
	t_table *table = (t_table *)data;
	while (table->eat_num > 0)
	{
		eat(table);
		ft_sleep(table);
		ft_think(table);
		table->eat_num --;
	}
	return (NULL);
}

size_t ft_gettime()
{
	struct timeval timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void philo_born(t_table *table)
{
	struct s_philo *philo;
	int i;

	i = 0;
	philo = malloc(sizeof(philo) * table->number_of_philosophers);
	table->ph = malloc(sizeof(pthread_t) * table->number_of_philosophers);
	table->philo = philo;
	
	table->start_time = ft_gettime();
	while (i < table->number_of_philosophers)
	{
		philo->id = i + 1;
		pthread_create(&table->ph[i], NULL, &rotune, table);
		pthread_join(table->ph[i], NULL);
		i ++;
	}
}

 void philo_table(t_table *table, char **av, int ac)
 {
	table->number_of_philosophers = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	if (ac == 5)
		table->eat_num = -1;
	else
		table->eat_num = atoi(av[5]);
	if (table->number_of_philosophers > 200)
		(write(1, "Wrong input: Wrong Number!\n", 28), exit(1));
	if (table->number_of_philosophers <= 0 || table->time_to_die <= 0
	|| table->time_to_sleep <= 0)
		(write(1, "Wrong input: Wrong Number!\n", 28), exit(1));
	philo_born(table);
 }

int main (int ac, char **av)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (exit(1), write(1, "malloc: error\n", 15), 1);
	if (ac == 6 || ac == 5)
	{
		philo_parser(av);
		philo_table(table, av, ac);
	}
	else
		(free(table), write(1, "Wrong input: Need 6 or 5 args\n", 31), exit(1));
	return (0);
}