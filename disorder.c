/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:36:38 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/13 12:36:52 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_mistakes(t_stack *stack, int *mistakes, int *total_pairs)
{
	t_stack	*anchor;
	t_stack	*candidate;

	anchor = stack;
	while (anchor)
	{
		candidate = anchor->next;
		while (candidate)
		{
			(*total_pairs)++;
			if (anchor->value > candidate->value)
				(*mistakes)++;
			candidate = candidate->next;
		}
		anchor = anchor->next;
	}
}

double	calculate_disorder(t_stack *stack)
{
	int	mistakes;
	int	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	count_mistakes(stack, &mistakes, &total_pairs);
	if (total_pairs == 0)
		return (0.0);
	return ((double)mistakes / (double)total_pairs);
}
