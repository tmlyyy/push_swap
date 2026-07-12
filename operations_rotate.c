/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* operations_rotate.c                                :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: gproenca <gproenca@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/07/09 14:11:53 by thamoliv          #+#    #+#             */
/* Updated: 2026/07/11 23:00:00 by gproenca         ###   ########.fr       */
/* */
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
