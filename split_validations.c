/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:25:21 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 19:55:24 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_split_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	fill_split_values(char **args, long *vals, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!string_is_valid_integer(args[i]) || ft_strlen(args[i]) > 11)
		{
			free(vals);
			print_error_and_exit();
		}
		vals[i] = ft_atol(args[i]);
		if (vals[i] > INT_MAX || vals[i] < INT_MIN)
		{
			free(vals);
			print_error_and_exit();
		}
		free(args[i]);
		i++;
	}
	free(args);
}

void	handle_multiple_args(int argc, char **argv, int start, t_data *data)
{
	long	*vals;
	int		total;

	total = argc - start;
	vals = malloc(sizeof(long) * total);
	if (!vals)
		print_error_and_exit();
	fill_values_array(argc, argv, start, vals);
	if (has_duplicate_values(vals, total))
	{
		free(vals);
		print_error_and_exit();
	}
	create_stack_from_values(data, vals, total);
	free(vals);
}
