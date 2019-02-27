/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:15:36 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/25 11:01:00 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_live(t_vm *vm, t_process *process)
{
	int		i;

	i = 0;
	while (i < vm->nbr_champ)
	{
		if (vm->champs[i].number == process->instruction.value[0])
		{
			vm->champs[i].lives = vm->arena.total_cycle;
			(vm->champs[i].lives_since_last_check)++;
			vm->arena.winner = i;
			if (vm->visu == 0)
				ft_printf("A process shows that player %d (%s) is alive\n",\
				process->instruction.value[0],\
				vm->champs[i].code.header.prog_name);
			break ;
		}
		i++;
	}
	process->lives_since_check++;
	vm->arena.lives_since_last_check++;
	process->pc = (process->pc + 5) % MEM_SIZE;
}
