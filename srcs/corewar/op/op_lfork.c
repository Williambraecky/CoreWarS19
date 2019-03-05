/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:15:36 by sde-spie          #+#    #+#             */
/*   Updated: 2019/03/05 13:36:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_lfork(t_vm *vm, t_process *process)
{
	int		n_proc;
	int		old_proc;

	n_proc = vm->arena.nbr_process;
	if (n_proc == vm->arena.s_proc)
	{
		old_proc = process->number;
		if (!(vm->arena.process = realloc(vm->arena.process,
					sizeof(t_process) * (vm->arena.s_proc * 2))))
			error_exit(vm, "Error: process allocation failed.");
		vm->arena.s_proc *= 2;
		process = &vm->arena.process[old_proc];
	}
	ft_memcpy((t_process *)&(vm->arena.process[n_proc]), (t_process*)process,\
			sizeof(t_process));
	vm->arena.process[n_proc].pc = mod(process->pc +\
			process->instruction.value[0]);
	vm->arena.process[n_proc].number = n_proc;
	vm->arena.process[n_proc].instruction.op_code = 0;
	vm->arena.process[n_proc].lives_since_check = 0;
	(vm->arena.nbr_process)++;
	(vm->arena.nbr_process_alive)++;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->sounds_born = 1;
}
