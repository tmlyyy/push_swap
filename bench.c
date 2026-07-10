/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:15:26 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 16:50:28 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bench_init(t_bench *bench, t_config *config, double disorder)
{
	bench->enabled = config->bench_enabled;
	bench->total = 0;
	bench->sa = 0;
	bench->sb = 0;
	bench->ss = 0;
	bench->ra = 0;
	bench->rb = 0;
	bench->rr = 0;
	bench->rra = 0;
	bench->rrb = 0;
	bench->rrr = 0;
	bench->pa = 0;
	bench->pb = 0;
	bench->count_only = config->count_only;
	bench->disorder = disorder;
	bench->strategy = config->strategy;
}

static int	get_op_nm(char *op)
{
	if (strings_are_equal(op, "sa"))
		return (1);
	if (strings_are_equal(op, "sb"))
		return (2);
	if (strings_are_equal(op, "ss"))
		return (3);
	if (strings_are_equal(op, "ra"))
		return (4);
	if (strings_are_equal(op, "rb"))
		return (5);
	if (strings_are_equal(op, "rr"))
		return (6);
	if (strings_are_equal(op, "rra"))
		return (7);
	if (strings_are_equal(op, "rrb"))
		return (8);
	if (strings_are_equal(op, "rrr"))
		return (9);
	if (strings_are_equal(op, "pa"))
		return (10);
	if (strings_are_equal(op, "pb"))
		return (11);
	return (0);
}

void	bench_count(t_bench *bench, char *op)
{
	int	nm;

	if (!bench || !bench->enabled)
		return ;
	bench->total++;
	nm = get_op_nm(op);
	bench->sa += (nm == 1);
	bench->sb += (nm == 2);
	bench->ss += (nm == 3);
	bench->ra += (nm == 4);
	bench->rb += (nm == 5);
	bench->rr += (nm == 6);
	bench->rra += (nm == 7);
	bench->rrb += (nm == 8);
	bench->rrr += (nm == 9);
	bench->pa += (nm == 10);
	bench->pb += (nm == 11);
}

static void	print_op_count(char *label, int count)
{
	if (count > 0)
	{
		putstr_fd(label, 2);
		putstr_fd(": ", 2);
		putnbr_fd(count, 2);
		putstr_fd(" | ", 2);
	}
}

void	bench_print(t_bench *b)
{
	if (!b || !b->enabled)
		return ;
	if (b->count_only)
	{
		putnbr_fd(b->total, 1);
		putstr_fd("\n", 1);
		return ;
	}
	print_strategy(b);
	print_disorder(b->disorder);
	putstr_fd("Total: ", 2);
	putnbr_fd(b->total, 2);
	putstr_fd("\n", 2);
	print_op_count("sa", b->sa);
	print_op_count("sb", b->sb);
	print_op_count("ra", b->ra);
	print_op_count("rb", b->rb);
	print_op_count("pa", b->pa);
	print_op_count("pb", b->pb);
	putstr_fd("\n", 2);
}
