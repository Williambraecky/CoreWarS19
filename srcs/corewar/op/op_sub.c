/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:15:36 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 14:24:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_sub(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			sub;

	(void)vm;
	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		sub = process->registre[val[0]] - process->registre[val[1]];
		process->registre[val[2]] = sub;
		process->carry = (sub == 0);
	}
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
}
