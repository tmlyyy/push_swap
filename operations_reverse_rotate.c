/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:37:49 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/13 12:37:51 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_rra(t_data *data, int print)
{
	rotate_down(&data->stack_a);
	if (print)
		print_operation("rra");
	bench_count(data->bench, "rra");
}

void	op_rrb(t_data *data, int print)
{
	rotate_down(&data->stack_b);
	if (print)
		print_operation("rrb");
	bench_count(data->bench, "rrb");
}

void	op_rrr(t_data *data, int print)
{
	rotate_down(&data->stack_a);
	rotate_down(&data->stack_b);
	if (print)
		print_operation("rrr");
	bench_count(data->bench, "rrr");
}
