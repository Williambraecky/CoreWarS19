/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:13:08 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:30:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			set_process(t_vm *vm, t_process *process)
{
	int			i;

	i = REG_NUMBER;
	vm->arena.nbr_process++;
	vm->arena.nbr_process_alive++;
	process->index_arena = 0;
	process->index_champ = 0;
	process->alive = 1;
	while (i--)
		process->registre[i] = 0;
	process->pc = 0;
	process->carry = 0;
	process->lives_since_check = 0;
	process->number = vm->arena.nbr_process;
}
