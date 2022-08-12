/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:40:18 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:40:25 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_mutex(t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->num_of_phil)
		pthread_mutex_destroy(&(param->m_forks[i]));
	pthread_mutex_destroy(&(param->m_print));
	pthread_mutex_destroy(&(param->m_dead));
	pthread_mutex_destroy(&(param->mutex));
	free(param->m_forks);
}

int	ft_free(t_param *param, char *str)
{
	usleep(5000);
	ft_free_mutex(param);
	free(param->philos);
	free(param);
	if (str)
		printf("%s", str);
	return (-1);
}
