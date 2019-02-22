/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/22 17:38:46 by sde-spie         ###   ########.fr       */
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
	while (i-- > 0)
	{
		if (vm->arena.process[i].alive)
		{
			index = vm->arena.process[i].pc;
			if (vm->arena.arena_owner[index] > 0)
				vm->arena.arena_owner[index] *= -1;
		}
	}
}
