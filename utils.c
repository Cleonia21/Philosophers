/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:59:54 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 17:09:06 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_and_return(char *str, int retval)
{
	printf("%s", str);
	return (retval);
}

t_my_time	get_time(t_philo *philo)
{
	struct timeval	tv;

	if (memset(&tv, 0, sizeof(struct timeval)) == NULL)
	{
		philo->param->finish_flag = -1;
		return (-1);
	}
	if (gettimeofday(&tv, NULL) == -1)
	{
		philo->param->finish_flag = -1;
		return (-1);
	}
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void	ft_usleep(t_my_time finish, t_philo *philo)
{
	t_my_time	start;

	start = get_time(philo);
	while (1)
	{
		usleep(50);
		if (get_time(philo) - start >= finish)
			break ;
	}
}
