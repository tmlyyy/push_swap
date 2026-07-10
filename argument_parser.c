/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:31:31 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 19:30:58 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	strategy_option(const char *str)
{
	if (strings_are_equal(str, "--simple")
		|| strings_are_equal(str, "--medium")
		|| strings_are_equal(str, "--complex")
		|| strings_are_equal(str, "--adaptive"))
		return (1);
	return (0);
}

int	has_duplicate_values(long *values, int total)
{
	int	i;
	int	j;

	i = 0;
	while (i < total)
	{
		j = i + 1;
		while (j < total)
		{
			if (values[i] == values[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_values_array(int argc, char **argv, int start, long *values)
{
	int		i;
	long	val;

	i = start;
	while (i < argc)
	{
		if (!string_is_valid_integer(argv[i]) || ft_strlen(argv[i]) > 11)
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

static void	handle_split_input(t_data *data, char *str)
{
	char	**args;
	long	*vals;
	int		count;

	args = ft_split(str, ' ');
	count = count_split_args(args);
	vals = malloc(sizeof(long) * count);
	if (!vals)
		print_error_and_exit();
	fill_split_values(args, vals, count);
	if (has_duplicate_values(vals, count))
	{
		free(vals);
		print_error_and_exit();
	}
	create_stack_from_values(data, vals, count);
	free(vals);
}

void	read_and_validate_arguments(int argc, char **argv, t_data *data)
{
	int	start;

	start = 1;
	if (argc > 1 && strategy_option(argv[1]))
		start = 2;
	if (argc == start + 1)
		handle_split_input(data, argv[start]);
	else if (argc > start)
		handle_multiple_args(argc, argv, start, data);
	else
		exit(0);
}
