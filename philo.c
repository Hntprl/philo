/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:01 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/15 20:23:53 by amarouf          ###   ########.fr       */
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

void	*rotune(void *data)
{
	t_philo *philo = (t_philo *)data;
	while (1)
	{
		if (philo->table->eat_num != -1 && philo->table->eat_num == philo->eat_num)
			return (NULL);
		eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

size_t ft_gettime()
{
	struct timeval timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	mutex_init(t_table *table)
{
	int i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i ++;
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->eat_mutex, NULL);
}

void	*monitor (void *data)
{
	int	ext;
	int death_count;
	int i;
	t_philo	*philo = (t_philo *)data;
	ext = 1;
	while (1)
	{
		i = 0;
		while (i < philo->table->number_of_philosophers)
		{
			pthread_mutex_lock(&philo[i].table->death_mutex);
			death_count = ft_gettime() - philo[i].last_meal;
			if (death_count >= philo[i].table->time_to_die)
			{
				ft_printstate("died\n", &philo[i]);
				ext = 0;
				break;
			}
			if (philo->eat_num == philo->table->eat_num)
			{
				ext = 0;
				break;
			}
			pthread_mutex_unlock(&philo[i].table->death_mutex);
			i ++;
		}
		if (ext == 0)
			break;
	}
	return (NULL);
}

void philo_init(t_philo *philo, t_table *table)
{
	int i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		philo[i].table = table;
		philo[i].id = i + 1;
		philo[i].eat_num = 0;
		philo[i].l_fork = &philo->table->forks[i];
		philo[i].r_fork = &philo->table->forks[(i + 1) % philo->table->number_of_philosophers];
		philo[i].start_time = ft_gettime();
		philo[i].last_meal = philo[i].start_time;
		i ++;
	}
}

int philo_born(t_table *table)
{
	t_philo *philo;
	pthread_t mntr;
	int i;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);
	if (!philo || !table->forks)
		return (1);
	mutex_init(table);
	philo_init(philo, table);
	pthread_create(&mntr, NULL, monitor, philo);
	while (i < table->number_of_philosophers)
	{
		pthread_create(&philo[i].ph, NULL, rotune, &philo[i]);
		pthread_detach(philo[i].ph);
		i ++;
	}
	pthread_join(mntr, NULL);
	return (0);
}

 int philo_table(t_table *table, char **av, int ac)
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
		return (write(1, "Wrong input: Wrong Number!\n", 28), 1);
	if (table->number_of_philosophers <= 0 || table->time_to_die <= 0
	|| table->time_to_sleep <= 0)
		return (write(1, "Wrong input: Wrong Number!\n", 28), 1);
	if (philo_born(table) == 1)
		return (1);
	return (0);
 }

int main (int ac, char **av)
{
	t_table *table;

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
		return (free(table), write(1, "Wrong input: Need 6 or 5 args\n", 31), 1);
	return (0);
}