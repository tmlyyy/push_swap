/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_complex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:45:12 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/13 13:11:38 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	partition_a(t_data *data, int size, int print)
{
	int	pushed;
	int	rotated;
	int	i;
	int	pivot;

	pushed = 0;
	rotated = 0;
	i = size;
	pivot = get_median(data->stack_a, size);
	while (i-- > 0)
	{
		if (data->stack_a->index < pivot)
		{
			op_pb(data, print);
			pushed++;
		}
		else
		{
			op_ra(data, print);
			rotated++;
		}
	}
	if (size != data->size_a + pushed)
		while (rotated--)
			op_rra(data, print);
	return (pushed);
}

static int	partition_b(t_data *data, int size, int print)
{
	int	pushed;
	int	rotated;
	int	i;
	int	pivot;

	pushed = 0;
	rotated = 0;
	i = size;
	pivot = get_median(data->stack_b, size);
	while (i-- > 0)
	{
		if (data->stack_b->index >= pivot)
		{
			op_pa(data, print);
			pushed++;
		}
		else
		{
			op_rb(data, print);
			rotated++;
		}
	}
	if (size != data->size_b + pushed)
		while (rotated--)
			op_rrb(data, print);
	return (pushed);
}

void	quicksort_a(t_data *data, int size, int print)
{
	int	pushed;

	if (size <= 2)
	{
		if (size == 2 && data->stack_a->index > data->stack_a->next->index)
			op_sa(data, print);
		return ;
	}
	pushed = partition_a(data, size, print);
	quicksort_a(data, size - pushed, print);
	quicksort_b(data, pushed, print);
}

void	quicksort_b(t_data *data, int size, int print)
{
	int	pushed;

	if (size <= 2)
	{
		if (size == 2 && data->stack_b->index < data->stack_b->next->index)
			op_sb(data, print);
		while (size-- > 0)
			op_pa(data, print);
		return ;
	}
	pushed = partition_b(data, size, print);
	quicksort_a(data, pushed, print);
	quicksort_b(data, size - pushed, print);
}

void	algorithm_quicksort(t_data *data, int print)
{
	if (is_sorted(data->stack_a))
		return ;
	assign_indexes(data);
	quicksort_a(data, data->size_a, print);
}
