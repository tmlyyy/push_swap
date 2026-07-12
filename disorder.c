/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* disorder.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/07/07 19:08:34 by thamoliv          #+#    #+#             */
/* Updated: 2026/07/07 19:08:41 by thamoliv         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Para CADA no da pilha (anchor), conta quantos nos que vem
** DEPOIS dele (candidate, percorrendo anchor->next em diante)
** sao menores que ele. Cada vez que isso acontece e um
** "erro" (mistake): um numero maior aparecendo antes de um
** numero menor, exatamente como o pseudocodigo do sujeito
** descreve (a[i] > a[j] para i < j).
** total_pairs conta TODOS os pares possiveis, seja erro ou
** nao, para no final calcularmos a proporcao.
*/
static void	count_mistakes(t_stack *stack, int *mistakes, int *total_pairs)
{
	t_stack	*anchor;
	t_stack	*candidate;

	anchor = stack;
	while (anchor)
	{
		candidate = anchor->next;
		while (candidate)
		{
			(*total_pairs)++;
			if (anchor->value > candidate->value)
				(*mistakes)++;
			candidate = candidate->next;
		}
		anchor = anchor->next;
	}
}

/*
** Disorder = mistakes / total_pairs, um numero entre 0.0
** (pilha ja ordenada, nenhum erro) e 1.0 (pilha na pior ordem
** possivel, todo par e um erro).
** Caso especial: pilha com 0 ou 1 elemento nao tem NENHUM par
** para comparar (total_pairs = 0), o que causaria divisao por
** zero. Nesse caso a pilha ja esta, por definicao, ordenada,
** entao devolvemos 0.0 diretamente.
**
** IMPORTANTE: esta funcao deve ser chamada logo apos montar a
** pilha inicial, ANTES de qualquer sa/pa/ra/etc ser executada
** — o sujeito exige medir a desordem do estado ORIGINAL.
*/
double	calculate_disorder(t_stack *stack)
{
	int	mistakes;
	int	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	count_mistakes(stack, &mistakes, &total_pairs);
	if (total_pairs == 0)
		return (0.0);
	return ((double)mistakes / (double)total_pairs);
}
