/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:47:05 by amarouf           #+#    #+#             */
/*   Updated: 2024/08/15 17:46:29 by amarouf          ###   ########.fr       */
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
	size_t		start_time;
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_num;
	pthread_t	*ph;
	struct s_philo		*philo;
}			t_table;

struct s_philo
{
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
};

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	eat(t_table *table);
void	ft_sleep(t_table *table);
void	ft_think(t_table *table);
size_t	ft_gettime();
#endif