/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_eat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:04:15 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:19:56 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	t_my_time	time_buf;
	int			second;
	int			first;

	first = philo->first_fork;
	second = philo->second_fork;
	if (pthread_mutex_lock(&(philo->param->m_forks[first])))
		philo->param->finish_flag = -1;
	printer(philo, TAKE_FIRST_FORK, get_time(philo) - philo->start_time);
	if (pthread_mutex_lock(&(philo->param->m_forks[second])))
		philo->param->finish_flag = -1;
	printer(philo, TAKE_SECOND_FORK, get_time(philo) - philo->start_time);
	time_buf = get_time(philo);
	philo->time_last_eat = time_buf + philo->time_die;
	printer(philo, EAT, time_buf - philo->start_time);
	if (philo->num_of_meals > 0)
		philo->num_of_meals--;
	ft_usleep(philo->time_eat, philo);
	if (pthread_mutex_unlock(&(philo->param->m_forks[first])))
		philo->param->finish_flag = -1;
	if (pthread_mutex_unlock(&(philo->param->m_forks[second])))
		philo->param->finish_flag = -1;
}
