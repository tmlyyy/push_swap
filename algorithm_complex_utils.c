/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_complex_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:22:07 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 17:48:47 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* algorithm_complex_utils.c                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/07/10 15:22:07 by thamoliv          #+#    #+#             */
/* Updated: 2026/07/10 16:15:00 by thamoliv         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_smaller_in_range(t_stack *stack, int size, int value)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < size && stack)
	{
		if (stack->index < value)
			count++;
		stack = stack->next;
		i++;
	}
	return (count);
}

int	get_median(t_stack *stack, int size)
{
	t_stack	*node;
	int		i;
	int		diff;
	int		best_diff;
	int		median;

	node = stack;
	i = -1;
	best_diff = size + 1;
	median = stack->index;
	while (++i < size && node)
	{
		diff = count_smaller_in_range(stack, size, node->index) - (size / 2);
		if (diff < 0)
			diff = -diff;
		if (diff < best_diff)
		{
			best_diff = diff;
			median = node->index;
		}
		node = node->next;
	}
	return (median);
}

void	sort_three_a(t_data *data, int print)
{
	int	a;
	int	b;
	int	c;

	if (data->size_a < 3)
		return ;
	a = data->stack_a->index;
	b = data->stack_a->next->index;
	c = data->stack_a->next->next->index;
	if (a < c && c < b)
	{
		op_rra(data, print);
		op_sa(data, print);
	}
	else if (b < a && a < c)
		op_sa(data, print);
	else if (c < a && a < b)
		op_rra(data, print);
	else if (b < c && c < a)
		op_ra(data, print);
	else if (c < b && b < a)
	{
		op_sa(data, print);
		op_rra(data, print);
	}
}

void	sort_three_b(t_data *data, int print)
{
	int	a;
	int	b;
	int	c;

	if (data->size_b < 3)
		return ;
	a = data->stack_b->index;
	b = data->stack_b->next->index;
	c = data->stack_b->next->next->index;
	if (a < c && c < b)
	{
		op_rrb(data, print);
		op_sb(data, print);
	}
	else if (b < a && a < c)
		op_sb(data, print);
	else if (c < a && a < b)
		op_rrb(data, print);
	else if (b < c && c < a)
		op_rb(data, print);
	else if (c < b && b < a)
	{
		op_sb(data, print);
		op_rrb(data, print);
	}
}
