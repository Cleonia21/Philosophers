/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:09:12 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:32:18 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor_printer(t_param *param, int i, int var)
{
	if (var == 1)
	{
		pthread_mutex_lock(&(param->m_print));
		printf("%lu %i died\n", get_time(param->philos)
			- param->philos[i].start_time, param->philos[i].num);
		pthread_mutex_unlock(&(param->m_dead));
		return (NULL);
	}
	if (var == 2)
	{
		pthread_mutex_lock(&param->m_print);
		pthread_mutex_unlock(&(param->m_dead));
		return (NULL);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_param	*param;
	int		i;
	int		sum;

	param = (t_param *)arg;
	while (1)
	{
		i = 0;
		sum = 0;
		while (i < param->num_of_phil)
		{
			if (param->philos[i].time_last_eat < get_time(param->philos))
				return (monitor_printer(param, i, 1));
			if (param->philos[i].num_of_meals == 0)
				sum++;
			i++;
		}
		if (sum == param->num_of_phil)
			return (monitor_printer(param, i, 2));
		usleep(500);
	}
	return (NULL);
}
