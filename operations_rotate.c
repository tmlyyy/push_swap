/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamoliv <thamoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:11:53 by thamoliv          #+#    #+#             */
/*   Updated: 2026/07/09 14:12:15 by thamoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** ra: gira a pilha a para cima (topo vira fundo).
** A logica do movimento em si (rotate_up) mora em
** node_helpers.c, porque e a MESMA logica usada por rb —
** so muda em qual pilha ela e aplicada.
*/
void	op_ra(t_data *data, int print)
{
	rotate_up(&data->stack_a);
	if (print)
		print_operation("ra");
}

void	op_rb(t_data *data, int print)
{
	rotate_up(&data->stack_b);
	if (print)
		print_operation("rb");
}

/*
** rr = ra e rb ao mesmo tempo. Chamamos rotate_up direto (sem
** passar por op_ra/op_rb) para nao imprimir "ra" e "rb"
** separadamente — so imprimimos "rr" uma vez no final.
*/
void	op_rr(t_data *data, int print)
{
	rotate_up(&data->stack_a);
	rotate_up(&data->stack_b);
	if (print)
		print_operation("rr");
}