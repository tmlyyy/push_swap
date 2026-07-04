/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:44:48 by thamoliv          #+#    #+#             */
/*   Updated: 2026/06/30 18:45:03 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_stack_top_to_bottom(t_stack *stack)
{
	while (stack)
	{
		printf("%d\n", stack->value);
		stack = stack->next;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.stack_a = NULL;
	data.stack_b = NULL;
	data.size_a = 0;
	data.size_b = 0;
	read_and_validate_arguments(argc, argv, &data);
	print_stack_top_to_bottom(data.stack_a);
	return (0);
}
