/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 12:37:08 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/13 12:37:14 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*get_strategy(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (strings_are_equal(argv[i], "--simple")
			|| strings_are_equal(argv[i], "--medium")
			|| strings_are_equal(argv[i], "--complex")
			|| strings_are_equal(argv[i], "--adaptive"))
			return (argv[i]);
		i++;
	}
	return ("--adaptive");
}

static int	has_bench_flag(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (strings_are_equal(argv[i], "--bench"))
			return (1);
		i++;
	}
	return (0);
}

static void	init_data(t_data *data)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	data->size_a = 0;
	data->size_b = 0;
	data->total_size = 0;
	data->bench = NULL;
}

static void	sort_stack(t_data *data, char *strategy)
{
	assign_indexes(data);
	if (is_sorted(data->stack_a))
		return ;
	if (strings_are_equal(strategy, "--simple"))
		algorithm_selection(data);
	else if (strings_are_equal(strategy, "--medium"))
		algorithm_chunk(data, 1);
	else if (strings_are_equal(strategy, "--complex"))
		algorithm_quicksort(data, 1);
	else if (data->size_a == 2)
		op_sa(data, 1);
	else if (data->size_a == 3)
		sort_three_a(data, 1);
	else if (data->size_a <= 5)
		algorithm_selection(data);
	else
		algorithm_chunk(data, 1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_bench		bench;
	t_config	config;

	if (argc < 2)
		return (0);
	init_data(&data);
	read_and_validate_arguments(argc, argv, &data);
	data.total_size = data.size_a;
	config.strategy = get_strategy(argc, argv);
	config.bench_enabled = has_bench_flag(argc, argv);
	config.count_only = 0;
	if (config.bench_enabled)
	{
		bench_init(&bench, &config, calculate_disorder(data.stack_a));
		data.bench = &bench;
	}
	sort_stack(&data, config.strategy);
	if (config.bench_enabled)
		bench_print(&bench);
	free_stack(&data.stack_a);
	free_stack(&data.stack_b);
	return (0);
}
