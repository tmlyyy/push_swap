/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:02:17 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/07 19:02:28 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_top_two(t_stack **stack)
{
	int	temp;

	if (!*stack || !(*stack)->next)
		return ;
	temp = (*stack)->value;
	(*stack)->value = (*stack)->next->value;
	(*stack)->next->value = temp;
}

void	op_sa(t_data *data, int print)
{
	swap_top_two(&data->stack_a);
	if (print)
		print_operation("sa");
}

void	op_sb(t_data *data, int print)
{
	swap_top_two(&data->stack_b);
	if (print)
		print_operation("sb");
}

void	op_ss(t_data *data, int print)
{
	swap_top_two(&data->stack_a);
	swap_top_two(&data->stack_b);
	if (print)
		print_operation("ss");
}
