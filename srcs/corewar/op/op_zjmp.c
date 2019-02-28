/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:15:36 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 14:35:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_zjmp(t_vm *vm, t_process *process)
{
	int		n_pc;

	(void)vm;
	if (process->carry == 1)
		n_pc = mod(process->pc + process->instruction.value[0] % IDX_MOD);
	else
		n_pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	process->pc = n_pc;
}
