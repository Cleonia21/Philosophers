/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:52:39 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:40:09 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	printer(philo, THINK, get_time(philo) - philo->start_time);
	if (philo->param->num_of_phil == 1)
	{
		if (pthread_mutex_lock(&(philo->param->m_forks[0])))
			philo->param->finish_flag = -1;
		printer(philo, TAKE_FIRST_FORK, get_time(philo) - philo->start_time);
	}
	while (philo->param->finish_flag == 0)
	{
		p_eat(philo);
		printer(philo, SlEEP, get_time(philo) - philo->start_time);
		ft_usleep(philo->time_sleep, philo);
		printer(philo, THINK, get_time(philo) - philo->start_time);
	}
	return (NULL);
}

int	philo_start(t_param *param)
{
	int			i;
	int			retval;
	pthread_t	pthread;

	retval = 0;
	i = 0;
	while (i < param->num_of_phil)
	{
		retval += pthread_create(&pthread, NULL, philosopher,
				(void *)(&param->philos[i]));
		retval += pthread_detach(pthread);
		i++;
		usleep(1000);
	}
	return (retval);
}

/*
 *	int fd = open("result", O_WRONLY | O_CREAT | O_TRUNC, 0644);
 *	dup2(fd, STDOUT_FILENO);
 *	close(fd);
*/
int	main(int argc, char **argv)
{
	t_param		*param;
	pthread_t	pthread;
	int			retval;

	retval = 0;
	param = initial_param(argc, argv);
	if (!param)
		return (print_and_return("error\n", ERROR));
	retval += pthread_create(&pthread, NULL, monitor, (void *)param);
	retval += pthread_detach(pthread);
	retval = philo_start(param);
	if (retval != 0)
		return (ft_free(param, "error\n"));
	retval += pthread_mutex_lock(&(param->m_dead));
	retval += pthread_mutex_unlock(&(param->m_dead));
	ft_free(param, NULL);
	if (retval != 0)
		return (print_and_return("error\n", ERROR));
	return (0);
}
