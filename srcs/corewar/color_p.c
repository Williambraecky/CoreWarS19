/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:29:06 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		reset_p_color(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->arena.arena_owner[i] < 0)
			vm->arena.arena_owner[i] *= -1;
		i++;
	}
}

void		setup_p_color(t_vm *vm)
{
	int		i;
	int		index;

	i = vm->arena.s_proc;
	while (i--)
	{
		if (vm->arena.process[i].alive)
		{
			index = vm->arena.process[i].pc;
			if (vm->arena.arena_owner[index] > 0)
				vm->arena.arena_owner[index] *= -1;
		}
	}
}
