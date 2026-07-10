/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gproenca <gproenca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:22:07 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/10 17:48:46 by gproenca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size_a;
	int		size_b;
	int		total_size;
}	t_data;

typedef struct s_config
{
	int		bench_enabled;
	int		count_only;
	char	*strategy;
}	t_config;

typedef struct s_bench
{
	int		enabled;
	int		total;
	int		sa;
	int		sb;
	int		ss;
	int		ra;
	int		rb;
	int		rr;
	int		rra;
	int		rrb;
	int		rrr;
	int		pa;
	int		pb;
	int		count_only;
	double	disorder;
	char	*strategy;
}	t_bench;

void	print_error_and_exit(void);
int		strings_are_equal(const char *str1, const char *str2);
int		string_is_valid_integer(const char *str);
long	ft_atol(const char *str);
void	print_operation(const char *name);
int		strategy_option(const char *str);
int		has_duplicate_values(long *values, int total_values);
void	read_and_validate_arguments(int argc, char **argv, t_data *data);
t_stack	*create_new_node(int value);
void	add_node_to_end_of_stack(t_stack **stack, t_stack *new_node);
int		count_stack_elements(t_stack *stack);
void	free_stack(t_stack **stack);
void	create_stack_from_values(t_data *data, long *values, int total_values);
t_stack	*pop_top(t_stack **stack);
void	push_top(t_stack **stack, t_stack *node);
t_stack	*pop_bottom(t_stack **stack);
void	rotate_up(t_stack **stack);
void	rotate_down(t_stack **stack);
void	op_sa(t_data *data, int print);
void	op_sb(t_data *data, int print);
void	op_ss(t_data *data, int print);
void	op_pa(t_data *data, int print);
void	op_pb(t_data *data, int print);
void	op_ra(t_data *data, int print);
void	op_rb(t_data *data, int print);
void	op_rr(t_data *data, int print);
void	op_rra(t_data *data, int print);
void	op_rrb(t_data *data, int print);
void	op_rrr(t_data *data, int print);
void	assign_indexes(t_data *data);
int		is_sorted(t_stack *stack);
int		find_position(t_stack *stack, int index);
int		stack_min_index(t_stack *stack);
int		stack_max_index(t_stack *stack);
void	algorithm_selection(t_data *data);
void	algorithm_chunk(t_data *data, int print);
void	algorithm_quicksort(t_data *data, int print);
void	quicksort_a(t_data *data, int size, int print);
void	quicksort_b(t_data *data, int size, int print);
int		get_median(t_stack *stack, int size);
void	sort_three_a(t_data *data, int print);
void	sort_three_b(t_data *data, int print);
double	calculate_disorder(t_stack *stack);
void	bench_init(t_bench *bench, t_config *config, double disorder);
void	bench_count(t_bench *bench, char *op);
void	bench_print(t_bench *bench);
void	putstr_fd(char *str, int fd);
void	putnbr_fd(int n, int fd);
void	print_strategy(t_bench *bench);
void	print_disorder(double disorder);

#endif