/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:15:40 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 17:48:47 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
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
	if (!bench->strategy)
		return ;
	if (strings_are_equal(bench->strategy, "--simple"))
		putstr_fd("Strategy: Simple\n", 2);
	else if (strings_are_equal(bench->strategy, "--medium"))
		putstr_fd("Strategy: Medium\n", 2);
	else if (strings_are_equal(bench->strategy, "--complex"))
		putstr_fd("Strategy: Complex\n", 2);
}

void	print_disorder(double disorder)
{
	int	percent;
	int	decimal;

	percent = (int)(disorder * 100);
	decimal = (int)(disorder * 10000) % 100;
	putstr_fd("Disorder: ", 2);
	putnbr_fd(percent, 2);
	putstr_fd(".", 2);
	if (decimal < 10)
		putstr_fd("0", 2);
	putnbr_fd(decimal, 2);
	putstr_fd("%\n", 2);
}
