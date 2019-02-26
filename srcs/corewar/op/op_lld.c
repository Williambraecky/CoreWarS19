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

void			op_lld(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		if (type[0] == T_IND)
			val[0] = big_end_toi(vm->arena.arena,
				(process->pc + val[0]) & 0xFFF, REG_SIZE);
		process->carry = (val[0] == 0);
		process->registre[val[1]] = val[0];
	}
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
}
