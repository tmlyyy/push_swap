/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:31:31 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 17:39:27 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	strategy_option(const char *str)
{
	if (strings_are_equal(str, "--simple"))
		return (1);
	if (strings_are_equal(str, "--medium"))
		return (1);
	if (strings_are_equal(str, "--complex"))
		return (1);
	if (strings_are_equal(str, "--adaptive"))
		return (1);
	return (0);
}

int	has_duplicate_values(long *values, int total_values)
{
	int	i;
	int	j;

	i = 0;
	while (i < total_values)
	{
		j = i + 1;
		while (j < total_values)
		{
			if (values[i] == values[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	fill_values_array(int argc, char **argv, int start, long *values)
{
	int		i;
	long	val;

	i = start;
	while (i < argc)
	{
		if (!string_is_valid_integer(argv[i]))
		{
			free(values);
			print_error_and_exit();
		}
		val = ft_atol(argv[i]);
		if (val > INT_MAX || val < INT_MIN)
		{
			free(values);
			print_error_and_exit();
		}
		values[i - start] = val;
		i++;
	}
}

void	read_and_validate_arguments(int argc, char **argv, t_data *data)
{
	long	*values;
	int		start_idx;
	int		total_vals;

	start_idx = 1;
	if (argc > 1 && strategy_option(argv[1]))
		start_idx = 2;
	total_vals = argc - start_idx;
	if (total_vals <= 0)
		exit(0);
	values = malloc(sizeof(long) * total_vals);
	if (!values)
		print_error_and_exit();
	fill_values_array(argc, argv, start_idx, values);
	if (has_duplicate_values(values, total_vals))
	{
		free(values);
		print_error_and_exit();
	}
	create_stack_from_values(data, values, total_vals);
	free(values);
}
