/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* operations_swap.c                                  :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/07/07 19:02:17 by thamoliv          #+#    #+#             */
/* Updated: 2026/07/11 23:00:00 by thamoliv         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_top_two(t_stack **stack)
{
	int	temp_value;
	int	temp_index;

	if (!*stack || !(*stack)->next)
		return ;
	temp_value = (*stack)->value;
	temp_index = (*stack)->index;
	(*stack)->value = (*stack)->next->value;
	(*stack)->index = (*stack)->next->index;
	(*stack)->next->value = temp_value;
	(*stack)->next->index = temp_index;
}

void	op_sa(t_data *data, int print)
{
	swap_top_two(&data->stack_a);
	if (print)
		print_operation("sa");
	bench_count(data->bench, "sa");
}

void	op_sb(t_data *data, int print)
{
	swap_top_two(&data->stack_b);
	if (print)
		print_operation("sb");
	bench_count(data->bench, "sb");
}

void	op_ss(t_data *data, int print)
{
	swap_top_two(&data->stack_a);
	swap_top_two(&data->stack_b);
	if (print)
		print_operation("ss");
	bench_count(data->bench, "ss");
}
