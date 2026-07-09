/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:15:40 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 16:15:43 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void	putnbr_fd(int n, int fd)
{
	char	c;

	if (n >= 10)
		putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

void	print_strategy(t_bench *bench)
{

}

void	print_disorder(double disorder)
{
	int	percent;
	int	decimal;

	percent = (int)(disorder * 10000);
	decimal = percent % 100;
	percent = percent / 100;
	putnbr_fd(percent, 2);
	putstr_fd(".", 2);
	if (decimal < 10)
		putstr_fd("0", 2);
	putnbr_fd(decimal, 2);
}

void	print_operations(t_bench *bench, char *op)
{
	if (bench && bench->count_only)
		return ;
	putstr_fd(op, 1);
}