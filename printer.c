/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:04:05 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 16:54:59 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*printer_util(int action)
{
	if (action == EAT)
		return ("is eating\n");
	else if (action == TAKE_FIRST_FORK)
		return ("has taken a fork\n");
	else if (action == TAKE_SECOND_FORK)
		return ("has taken a fork\n");
	else if (action == SlEEP)
		return ("is sleeping\n");
	else if (action == THINK)
		return ("is thinking\n");
	else if (action == DIE)
		return ("died\n");
	else if (action == END_FOR_LIMIT)
		return ("end for limit\n");
	return ("printer_error\n");
}

void	printer(t_philo *philo, int action, t_my_time time)
{
	if (pthread_mutex_lock(&philo->param->m_print))
		philo->param->finish_flag = -1;
	if (philo->param->finish_flag == 0)
		printf("%i %i %s", (int)time, philo->num, printer_util(action));
	if (pthread_mutex_unlock(&philo->param->m_print))
		philo->param->finish_flag = -1;
}
