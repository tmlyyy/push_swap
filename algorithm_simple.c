/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:19:17 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 18:22:53 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_smallest_to_top(t_data *data)
{
	int	pos;
	int	min;

	min = stack_min_index(data->stack_a);
	pos = find_position(data->stack_a, min);
	if (pos <= data->size_a / 2)
	{
		while (pos-- > 0)
			op_ra(data, 1);
	}
	else
	{
		pos = data->size_a - pos;
		while (pos-- > 0)
			op_rra(data, 1);
	}
}

static void	push_all_smallest(t_data *data)
{
	while (data->size_a > 0)
	{
		move_smallest_to_top(data);
		op_pb(data, 1);
	}
}

void	algorithm_selection(t_data *data)
{
	if (is_sorted(data->stack_a))
		return ;
	push_all_smallest(data);
	while (data->size_b > 0)
		op_pa(data, 1);
}
