/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 10:23:27 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/14 10:00:08 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		manage_processes(t_vm *vm)
{
	int			i;
	t_process	*pro;

	pro = vm->arena.process;
	i = vm->arena.nbr_process;
	while (i--)
		if (pro[i].alive)
		{
			if (pro[i].instruction.op_code == 0)
				pro[i].instruction = read_instruction(vm, pro[i].pc);
			if (pro[i].instruction.cycle_exec >= 0 && vm->arena.total_cycle < 50)
				printf("cycle = %d, cycle exec = %d\n", vm->arena.total_cycle ,pro[i].instruction.cycle_exec);
			pro[i].instruction.cycle_exec--;
			if (pro[i].instruction.cycle_exec == 0)
			{
				if (vm->arena.total_cycle < 50)
					printf("ca rentre!\n");
				op_get_params(vm, &pro[i]);
				if (vm->arena.total_cycle < 50)
				{
					printf("value 1 = %d\n", pro[i].instruction.value[0]);
					printf("value 2 = %d\n", pro[i].instruction.value[1]);
					printf("value 3 = %d\n", pro[i].instruction.value[2]);
				}
				pro[i].instruction.op(vm, pro[i]);
				ft_bzero(&pro[i].instruction, sizeof(t_instruct));
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
