/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:05:01 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/01 15:35:36 by thamoliv         ###   ########.fr       */
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
}	t_data;

/* error_handling.c
** Tudo relacionado a "algo deu errado, aborta o programa". */
void	print_error_and_exit(void);

/* string_validation.c
** Funcoes que olham para uma string (um argv[i]) e decidem
** se ela e um numero valido. */
int		stringhttps://prod.liveshare.vsengsaas.visualstudio.com/join?853BD1BBD7BB0C389F0F015E91A9D40BA80As_are_equal(const char *str1, const char *str2);
int		string_is_valid_integer(const char *str);

/* utils.c
** Conversao de string para numero. So deve ser chamada depois
** que string_is_valid_integer ja confirmou o formato. */
long	ft_atol(const char *str);

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

#endif