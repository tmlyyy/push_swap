/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:29:54 by thamoliv          #+#    #+#             */
/*   Updated: 2026/06/30 18:51:30 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*create_new_node(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		print_error_and_exit();
	node->value = value;
	node->index = 0;
	node->next = NULL;
	return (node);
}


void	add_node_to_end_of_stack(t_stack **stack, t_stack *new_node)
{
	t_stack	*current;

	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	current = *stack;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

int	count_stack_elements(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

void	create_stack_from_values(t_data *data, long *values, int total_values)
{
	int		i;
	t_stack	*new_node;
 
	i = 0;
	while (i < total_values)
	{
		new_node = create_new_node((int)values[i]);
		add_node_to_end_of_stack(&data->stack_a, new_node);
		i++;
	}
	data->size_a = count_stack_elements(data->stack_a);
	data->stack_b = NULL;
	data->size_b = 0;
}
 