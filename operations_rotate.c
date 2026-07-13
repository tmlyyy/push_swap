/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:37:54 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/13 12:37:55 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_ra(t_data *data, int print)
{
	rotate_up(&data->stack_a);
	if (print)
		print_operation("ra");
	bench_count(data->bench, "ra");
}

void	op_rb(t_data *data, int print)
{
	rotate_up(&data->stack_b);
	if (print)
		print_operation("rb");
	bench_count(data->bench, "rb");
}

void	op_rr(t_data *data, int print)
{
	rotate_up(&data->stack_a);
	rotate_up(&data->stack_b);
	if (print)
		print_operation("rr");
	bench_count(data->bench, "rr");
}
