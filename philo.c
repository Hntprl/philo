/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:01 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/18 21:05:44 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_parser(char **av)
{
	int	i;
	int	j;

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

void	philo_init(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		philo[i].table = table;
		philo[i].id = i + 1;
		philo[i].eat_num = 0;
		philo[i].r_fork = &philo->table->forks[i];
		philo[i].l_fork = &philo->table->forks[(i + 1) % table->philo_num];
		philo[i].start_time = ft_gettime();
		philo[i].last_meal = philo[i].start_time;
		i ++;
	}
}

int	philo_born(t_table *table)
{
	t_philo		*philo;
	pthread_t	mntr;
	int			i;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->philo_num);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!philo || !table->forks)
		return (1);
	mutex_init(table);
	philo_init(philo, table);
	while (i < table->philo_num)
	{
		pthread_create(&philo[i].ph, NULL, rotune, &philo[i]);
		pthread_detach(philo[i].ph);
		i ++;
	}
	pthread_create(&mntr, NULL, monitor, philo);
	pthread_join(mntr, NULL);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->eat_mutex);
	pthread_mutex_destroy(table->forks);
	free(philo);
	return (0);
}

int	philo_table(t_table *table, char **av, int ac)
{
	table->philo_num = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	if (ac == 5)
		table->eat_num = -1;
	else
		table->eat_num = atoi(av[5]);
	if (table->philo_num > 200)
		return (write(1, "Wrong input: Wrong Number!\n", 28), 1);
	if (table->philo_num <= 0 || table->time_to_die <= 0
		|| table->time_to_sleep <= 0)
		return (write(1, "Wrong input: Wrong Number!\n", 28), 1);
	if (philo_born(table) == 1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (write(1, "malloc: error\n", 15), 1);
	if (ac == 6 || ac == 5)
	{
		philo_parser(av);
		if (philo_table(table, av, ac) == 1)
			return (1);
	}
	else
		return (free(table), write(1, "Wrong input!\n", 14), 1);
	return (0);
}
