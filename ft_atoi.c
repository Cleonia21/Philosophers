/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:10:13 by cleonia           #+#    #+#             */
/*   Updated: 2021/12/08 14:10:14 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

static int	ft_helpmepls(const char *str, int symbol)
{
	int		a;
	int		len;

	a = 0;
	len = 0;
	while ((*str) >= '0' && (*str) <= '9')
	{
		a = a * 10 + *str++ - '0';
		if ((len == 19) && (symbol == -1))
			return (0);
		if (len == 19)
			return (-1);
		len++;
	}
	return (a);
}

int	ft_atoi(char *str)
{
	int		symbol;
	int		a;

	symbol = 1;
	while (*str == ' ' || *str == '\n' || *str == '\v'
		|| *str == '\t' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' && *(str + 1) != '+')
	{
		symbol = -1;
		str++;
	}
	if (*str == '+')
		str++;
	a = ft_helpmepls(str, symbol);
	if (a == 0 || a == -1)
		return (a);
	return (a * symbol);
}
