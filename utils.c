/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:38:19 by thamoliv          #+#    #+#             */
/*   Updated: 2026/06/30 18:49:33 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol(const char *str)
{
	long	res;
	int		sign;
	int		digit;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (sign == 1 && res > (INT_MAX - digit / 10))
			return ((long)INT_MAX + 1);
		if (sign == -1 && res > (2147483648 - digit / 10))
			return ((long)INT_MIN - 1);
		res = res * 10 + digit;
		str++;
	}
	return (res * sign);
}
