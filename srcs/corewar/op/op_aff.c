/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:15:36 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 14:33:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			op_aff(t_vm *vm, t_process *process)
{
	t_arg_type	*type;
	int			val;

	(void)vm;
	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value[0];
		ft_printf("%c", (char)(process->registre[val]));
	}
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
}
