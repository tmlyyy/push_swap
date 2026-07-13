/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:37:37 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/13 12:37:41 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_pa(t_data *data, int print)
{
	t_stack	*node;

	if (data->size_b > 0)
	{
		node = pop_top(&data->stack_b);
		push_top(&data->stack_a, node);
		data->size_b--;
		data->size_a++;
	}
	if (print)
		print_operation("pa");
	bench_count(data->bench, "pa");
}

void	op_pb(t_data *data, int print)
{
	t_stack	*node;

	if (data->size_a > 0)
	{
		node = pop_top(&data->stack_a);
		push_top(&data->stack_b, node);
		data->size_a--;
		data->size_b++;
	}
	if (print)
		print_operation("pb");
	bench_count(data->bench, "pb");
}
