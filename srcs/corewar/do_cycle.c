/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 10:23:27 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/22 12:11:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		manage_processes(t_vm *vm)
{
	int			i;

	i = vm->arena.nbr_process;
	while (i--)
		if (vm->arena.process[i].alive)
		{
			if (vm->arena.process[i].instruction.op_code == 0)
				vm->arena.process[i].instruction =
					read_instruction(vm, vm->arena.process[i].pc);
			vm->arena.process[i].instruction.cycle_exec--;
			if (vm->arena.process[i].instruction.cycle_exec == 0)
			{
				op_get_params(vm, &vm->arena.process[i]);
				vm->arena.process[i].instruction.op(vm, &vm->arena.process[i]);
				ft_bzero(&vm->arena.process[i].instruction, sizeof(t_instruct));
			}
		}
}

void		do_cycle(t_vm *vm)
{
	vm->sounds_death = 0;
	vm->arena.total_cycle++;
	vm->arena.cycle_since_check++;
	manage_processes(vm);
	check_end_cycle(vm);
}
