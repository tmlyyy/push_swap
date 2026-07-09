/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:15:26 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 16:15:33 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_op_nm(char *op)
{
	if (op[0] == 's' && op[1] == 'a')
		return (1);
	if (op[0] == 's' && op[1] == 'b')
		return (2);
	if (op[0] == 's' && op[1] == 's')
		return (3);
	if (op[0] == 'r' && op[1] == 'a' && op[2] == '\0')
		return (4);
	if (op[0] == 'r' && op[1] == 'b' && op[2] == '\0')
		return (5);
	if (op[0] == 'r' && op[1] == 'r' && op[2] == '\0')
		return (6);
	if (op[0] == 'r' && op[1] == 'r' && op[2] == 'a')
		return (7);
	if (op[0] == 'r' && op[1] == 'r' && op[2] == 'b')
		return (8);
	if (op[0] == 'r' && op[1] == 'r' && op[2] == 'r')
		return (9);
	if (op[0] == 'p' && op[1] == 'a')
		return (10);
	if (op[0] == 'p' && op[1] == 'b')
		return (11);
}

static void	bench_print_count(char *label, int count)
{
	putstr_fd(label, 2);
	putnbr_fd(count, 2);
}

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

void	bench_print(t_bench *bench)
{
	if (!bench || !bench->enabled)
		return ;
	if (bench->count_only)
	{
		putnbr_fd(bench->total, 1);
		putstr_fd("\n", 1);
		return ;
	}
	
}