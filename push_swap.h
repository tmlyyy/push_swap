/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:05:01 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 18:14:50 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
** Um "no" (node) da pilha. Pilha = lista encadeada onde
** "stack" (o ponteiro que guardamos em t_data) sempre aponta
** para o ELEMENTO DO TOPO. Empilhar = criar no e colocar
** na frente. Desempilhar = mover o ponteiro para o "next".
**
** value : o numero em si.
** index : posicao relativa (0 = menor valor, n-1 = maior valor)
**         dentro da pilha. Nao usamos ainda (passo 1), mas vai
**         ser essencial nos algoritmos (passo 4) para comparar
**         "rank" em vez de comparar numeros brutos.
** next  : proximo elemento abaixo na pilha.
*/
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/*
** Guarda o estado inteiro do programa em um unico lugar.
** Isso evita variaveis globais (proibidas pela Norma) e
** evita que cada funcao precise receber 6 parametros soltos.
*/
typedef struct s_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size_a;
	int		size_b;
	int		total_size;
}	t_data;

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
	double	disorder;
	char	*strategy;
}	t_bench;

typedef struct s_config
{
	int		bench_enabled;
	int		count_only;
	char	*strategy;
}	t_config;

/* error_handling.c
** Tudo relacionado a "algo deu errado, aborta o programa". */
void	print_error_and_exit(void);

/* string_validation.c
** Funcoes que olham para uma string (um argv[i]) e decidem
** se ela e um numero valido. */
int		strings_are_equal(const char *str1, const char *str2);
int		string_is_valid_integer(const char *str);

/* utils.c
** Conversao de string para numero (so deve ser chamada depois
** que string_is_valid_integer ja confirmou o formato), e
** impressao do nome de uma operacao executada, seguido de \n,
** exatamente no formato exigido pelo sujeito. */
long	ft_atol(const char *str);
void	print_operation(const char *name);

/* argument_parser.c
** Orquestra a leitura dos argumentos da linha de comando:
** identifica flag de estrategia, valida cada numero,
** rejeita duplicatas, e manda construir a pilha. */
int		strategy_option(const char *str);
int		has_duplicate_values(long *values, int total_values);
void	read_and_validate_arguments(int argc, char **argv, t_data *data);

/* stack_creation.c
** Funcoes "de fabrica": criam nos e montam a pilha inicial
** a partir dos valores ja validados. */
t_stack	*create_new_node(int value);
void	add_node_to_end_of_stack(t_stack **stack, t_stack *new_node);
int		count_stack_elements(t_stack *stack);
void	create_stack_from_values(t_data *data, long *values, int total_values);

/* node_helpers.c
** Movimentos "de baixo nivel" em uma unica pilha: tirar do
** topo, colocar no topo, tirar do fundo, e as duas rotacoes
** genericas (usadas tanto por ra/rb quanto por rra/rrb). */
t_stack	*pop_top(t_stack **stack);
void	push_top(t_stack **stack, t_stack *node);
t_stack	*pop_bottom(t_stack **stack);
void	rotate_up(t_stack **stack);
void	rotate_down(t_stack **stack);

/* operations_swap.c
** sa, sb, ss : trocam os 2 elementos do topo de a, de b, ou
** dos dois ao mesmo tempo. */
void	op_sa(t_data *data, int print);
void	op_sb(t_data *data, int print);
void	op_ss(t_data *data, int print);

/* operations_push.c
** pa, pb : movem o elemento do topo de uma pilha para o topo
** da outra. */
void	op_pa(t_data *data, int print);
void	op_pb(t_data *data, int print);

/* operations_rotate.c
** ra, rb, rr : primeiro elemento vira o ultimo. */
void	op_ra(t_data *data, int print);
void	op_rb(t_data *data, int print);
void	op_rr(t_data *data, int print);

/* operations_reverse_rotate.c
** rra, rrb, rrr : ultimo elemento vira o primeiro. */
void	op_rra(t_data *data, int print);
void	op_rrb(t_data *data, int print);
void	op_rrr(t_data *data, int print);

/* disorder.c
** Metrica obrigatoria (0.0 a 1.0) de quao longe a pilha esta
** de estar ordenada. Deve ser medida ANTES de qualquer
** operacao ser executada na pilha. */
double	compute_disorder(t_stack *stack);
static	void	count_mistakes(t_stack *stack, int *mistakes, int *total_pairs);

static	int	count_smaller_values(t_stack *stack, int value);
void	assign_indexes(t_data *data);

int	is_sorted(t_stack *stack);
int	find_position(t_stack *stack, int index);
int	stack_min_index(t_stack *stack);
int	stack_max_index(t_stack *stack);




#endif