/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse_rotate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:04:21 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/07 19:04:42 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_rra(t_data *data, int print)
{
	rotate_down(&data->stack_a);
	if (print)
		print_operation("rra");
}

void	op_rrb(t_data *data, int print)
{
	rotate_down(&data->stack_b);
	if (print)
		print_operation("rrb");
}

void	op_rrr(t_data *data, int print)
{
	rotate_down(&data->stack_a);
	rotate_down(&data->stack_b);
	if (print)
		print_operation("rrr");
}
