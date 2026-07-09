/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_complex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 17:45:12 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 18:50:59 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	partition_a(t_data *data, int size, int pivot)
{
	int	pushed;
	int	i;

	pushed = 0;
	i = 0;
	while (i < size)
	{
		if (data->stack_a->index < pivot)
		{
			op_pb(data, 1);
			pushed++;
		}
		else
		{
			op_ra(data, 1);
		}
		i++;
	}
	return (pushed);
}

void	quicksort_a(t_data *data, int size)
{
	int	pivot;
	int	pushed;
	int	i;

	pushed = 0;
	if (size <= 3)
	{
		sort_three_a(data);
		return ;
	}
	pivot = get_median(data->stack_a, size);
	pushed = partition_a(data, size, pivot);

	while (i-- > 0)
		op_rra(data, 1);
	quicksort_a(data, size - pushed);
	quicksort_b(data, pushed);
}
