/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:50:25 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:03:19 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_argv
{
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	phil_num;
	int	meals_num;
}	t_argv;

static int	initial_mutex(t_param *param, int p_n)
{
	int	retval;
	int	i;

	retval = 0;
	param->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p_n);
	if (!param->m_forks)
		return (-1);
	retval += pthread_mutex_init(&(param->m_print), NULL);
	retval += pthread_mutex_init(&(param->m_dead), NULL);
	retval += pthread_mutex_lock(&(param->m_dead));
	retval += pthread_mutex_init(&(param->mutex), NULL);
	i = -1;
	while (++i < p_n)
		retval += pthread_mutex_init(&(param->m_forks[i]), NULL);
	if (retval)
		free(param->m_forks);
	return (retval);
}

static void	initial_philos(t_param *param, t_argv my_argv)
{
	t_my_time	start_time;
	int			i;

	param->philos[0].param = param;
	start_time = get_time(&(param->philos[0]));
	i = 0;
	while (i < param->num_of_phil)
	{
		param->philos[i].num_of_meals = my_argv.meals_num;
		param->philos[i].param = param;
		param->philos[i].start_time = start_time;
		param->philos[i].num = i + 1;
		param->philos[i].time_die = my_argv.t_die;
		param->philos[i].time_eat = my_argv.t_eat;
		param->philos[i].time_last_eat = start_time + param->philos[i].time_die;
		param->philos[i].time_sleep = my_argv.t_sleep;
		param->philos[i].first_fork = i;
		param->philos[i].second_fork = i + 1;
		if (i + 1 == param->num_of_phil)
		{
			param->philos[i].first_fork = 0;
			param->philos[i].second_fork = i;
		}
		i++;
	}
}

static t_argv	initial_argv(int argc, char **argv)
{
	t_argv	my_argv;

	my_argv.phil_num = ft_atoi(argv[1]);
	my_argv.t_die = ft_atoi(argv[2]);
	my_argv.t_eat = ft_atoi(argv[3]);
	my_argv.t_sleep = ft_atoi(argv[4]);
	my_argv.meals_num = -1;
	if (argc == 6)
		my_argv.meals_num = ft_atoi(argv[5]);
	return (my_argv);
}

t_param	*initial_param(int argc, char **argv)
{
	t_param	*param;
	t_argv	my_argv;

	if (argc != 5 && argc != 6)
		return (NULL);
	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		return (NULL);
	my_argv = initial_argv(argc, argv);
	param->finish_flag = 0;
	param->num_of_phil = my_argv.phil_num;
	param->philos = (t_philo *) malloc(sizeof(t_philo) * param->num_of_phil);
	if (!param->philos)
	{
		free(param);
		return (NULL);
	}
	if (initial_mutex(param, param->num_of_phil) != 0)
	{
		free(param);
		free(param->philos);
		return (NULL);
	}
	initial_philos(param, my_argv);
	return (param);
}
