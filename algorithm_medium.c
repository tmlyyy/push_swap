/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_medium.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:44:15 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 20:27:42 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_size(int total)
{
	int	size;

	if (total <= 100)
		size = total / 5;
	else
		size = total / 11;
	if (size < 1)
		size = 1;
	return (size);
}

static void	move_chunk_to_b(t_data *data, int limit, int size, int print)
{
	int	scanned;

	scanned = data->size_a;
	while (scanned-- > 0 && data->size_a > 0)
	{
		if (data->stack_a->index <= limit)
		{
			op_pb(data, print);
			if (data->size_b > 1 && data->stack_b->index < (limit - (size / 2)))
				op_rb(data, print);
		}
		else
			op_ra(data, print);
	}
}

static void	push_chunks(t_data *data, int chunk_s, int print)
{
	int	current_limit;

	current_limit = chunk_s;
	while (data->size_a > 0)
	{
		move_chunk_to_b(data, current_limit, chunk_s, print);
		current_limit += chunk_s;
		if (current_limit > data->total_size)
			current_limit = data->total_size;
	}
}

static void	move_biggest_to_top(t_data *data, int print)--
{
	int	pos;
	int	max_idx;

	max_idx = stack_max_index(data->stack_b);
	pos = find_position(data->stack_b, max_idx);
	if (pos <= data->size_b / 2)
	{
		while (pos-- > 0)
			op_rb(data, print);
	}
	else
	{
		pos = data->size_b - pos;
		while (pos-- > 0)
			op_rrb(data, print);
	}
}

void	algorithm_chunk(t_data *data, int print)
{
	int	c_size;

	if (is_sorted(data->stack_a))
		return ;
	assign_indexes(data);
	c_size = chunk_size(data->size_a);
	push_chunks(data, c_size, print);
	while (data->size_b > 0)
	{
		move_biggest_to_top(data, print);
		op_pa(data, print);
	}
}
