/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 19:00:06 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/07 19:00:29 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*pop_top(t_stack **stack)
{
	t_stack	*top;

	if (!*stack)
		return (NULL);
	top = *stack;
	*stack = (*stack)->next;
	top->next = NULL;
	return (top);
}

void	push_top(t_stack **stack, t_stack *node)
{
	node->next = *stack;
	*stack = node;
}

t_stack	*pop_bottom(t_stack **stack)
{
	t_stack	*current;

	if (!*stack)
		return (NULL);
	if (!(*stack)->next)
		return (pop_top(stack));
	current = *stack;
	while (current->next->next)
		current = current->next;
	return (pop_top(&current->next));
}

void	rotate_up(t_stack **stack)
{
	t_stack	*node;

	if (!*stack || !(*stack)->next)
		return ;
	node = pop_top(stack);
	add_node_to_end_of_stack(stack, node);
}

void	rotate_down(t_stack **stack)
{
	t_stack	*node;

	if (!*stack || !(*stack)->next)
		return ;
	node = pop_bottom(stack);
	push_top(stack, node);
}
