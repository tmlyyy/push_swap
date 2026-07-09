/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 15:01:52 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 15:02:40 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_smaller_values(t_stack *stack, int value)
{
	int	count;

	count = 0;
	while (stack)
	{
		if (stack->value < value)
			count++;
		stack = stack->next;
	}
	return (count);
}

void	assign_indexes(t_data *data)
{
	t_stack	*current;

	current = data->stack_a;
	while (current)
	{
		current->index = count_smaller_values(data->stack_a,
				current->value);
		current = current->next;
	}
}
