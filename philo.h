/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:03:25 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:36:34 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <fcntl.h>

typedef unsigned long	t_my_time;

typedef struct s_philo
{
	t_my_time		time_die;
	t_my_time		time_eat;
	t_my_time		time_sleep;
	t_my_time		time_last_eat;
	t_my_time		start_time;
	int				num;
	int				num_of_meals;
	int				first_fork;
	int				second_fork;
	struct s_param	*param;
}	t_philo;

typedef struct s_param
{
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	mutex;
	int				num_of_phil;
	int				finish_flag;
	t_philo			*philos;
}	t_param;

int			print_and_return(char *str, int retval);
t_param		*initial_param(int argc, char **argv);
void		print_param(t_param *param);
void		printer(t_philo *philo, int action, t_my_time time);
int			ft_atoi(char *str);
void		*monitor(void *arg);
void		p_eat(t_philo *philo);
t_my_time	get_time(t_philo *philo);
void		ft_usleep(t_my_time finish, t_philo *philo);
int			ft_free(t_param *param, char *str);

enum	e_const
{
	TRUE = 1,
	FALSE = 0,
	ERROR = 1,
	NOT_ERROR = 0
};

enum	e_actions
{
	EAT = 1,
	SlEEP = 2,
	DIE = 3,
	THINK = 4,
	TAKE_FIRST_FORK = 5,
	TAKE_SECOND_FORK = 6,
	END_FOR_LIMIT = 7
};

#endif
