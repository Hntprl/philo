/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:05 by amarouf           #+#    #+#             */
/*   Updated: 2024/09/18 21:12:58 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_num;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	death_mutex;
}			t_table;

typedef struct s_philo
{
	pthread_t		ph;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_table			*table;
	size_t			start_time;
	int				eat_num;
	int				id;
	size_t			last_meal;
}	t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	eat(t_philo *philo);
void	ft_sleep_think(t_philo *philo);
size_t	ft_gettime(void);
void	ft_printstate(char *str, t_philo *philo);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*rotune(void *data);
void	mutex_init(t_table *table);
void	*monitor(void *data);
#endif