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

void			op_sti(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			i;
	int			sum;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		i = 0;
		val = process->instruction.value;
		while (i <= 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						mod(process->pc + val[i]), 4);
			i++;
		}
		sum = val[1] + val[2];
		lit_end_tovm(vm, mod(process->pc + sum % IDX_MOD),
			val[0], process->index_champ);
	}
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
}
