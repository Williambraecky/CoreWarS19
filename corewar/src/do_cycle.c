/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 10:23:27 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/31 17:35:44 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		manage_processes(t_vm *vm)
{
	int			i;
	t_process	*pro;

	pro = vm->arena.process;
	i = vm->arena.nbr_process;
	while (i--)
	{
		if (pro[i].alive)
		{
			if (pro[i].instruction.op_code == 0)
				pro[i].instruction = read_instruction(vm, pro[i].pc);
			pro[i].instruction.cycle_exec--;
			if (pro[i].instruction.cycle_exec == 0)
			{
				op_get_params(vm, &pro[i]);
				pro[i].instruction.op(vm, pro[i]);
				ft_bzero(&pro[i].instruction, sizeof(t_instruct));
			}
		}
	}
}

void		do_cycle(t_vm *vm)
{
	vm->arena.total_cycle++;
	vm->arena.cycle_since_check++;
	manage_processes(vm);
//	check_end_cycle(vm);
}
