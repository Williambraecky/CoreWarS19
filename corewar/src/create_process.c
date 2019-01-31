/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:13:08 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/31 14:14:22 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_process		*create_process(t_vm *vm)
{
	t_process	*new;
	int			i;

	i = -1;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		error_exit(vm, "Error while mallocing new process.");
	vm->arena.nbr_process++;
	vm->arena.nbr_process_alive++;
	new->index_arena = 0;
	new->index_champ = 0;
	new->alive = 1;
	while (++i < REG_NUMBER)
		new->registre[i] = 0;
	new->pc = 0;
	new->carry = 0;
	new->lives_since_check = 0;
	new->number = vm->arena.nbr_process;
	return (new);
}
