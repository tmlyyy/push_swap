/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:44:48 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 19:32:48 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_stack(t_data *data)
{
	assign_indexes(data);
	if (is_sorted(data->stack_a))
		return ;
	if (data->size_a == 2)
		op_sa(data, 1);
	else if (data->size_a == 3)
		sort_three_a(data, 1);
	else if (data->size_a <= 5)
		algorithm_selection(data);
	else if (data->size_a <= 100)
		algorithm_chunk(data, 1);
	else
		algorithm_quicksort(data, 1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	data.stack_a = NULL;
	data.stack_b = NULL;
	data.size_a = 0;
	data.size_b = 0;
	data.total_size = 0;
	read_and_validate_arguments(argc, argv, &data);
	data.total_size = data.size_a;
	sort_stack(&data);
	free_stack(&data.stack_a);
	free_stack(&data.stack_b);
	return (0);
}
