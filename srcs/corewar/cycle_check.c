/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:44:09 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:30:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		kill_process(t_vm *vm)
{
	int			i;
	t_process	*process;

	i = vm->arena.nbr_process;
	while (i--)
	{
		process = &vm->arena.process[i];
		if (process->alive && process->lives_since_check == 0)
		{
			process->alive = 0;
			vm->arena.nbr_process_alive--;
			vm->sounds_death = 1;
		}
		process->lives_since_check = 0;
	}
}

void		check_end_cycle(t_vm *vm)
{
	int		i;

	if (vm->arena.cycle_since_check >= vm->arena.cycle_to_die)
	{
		kill_process(vm);
		if (vm->arena.lives_since_last_check >= NBR_LIVE\
			|| vm->arena.check_count >= MAX_CHECKS)
		{
			vm->arena.cycle_to_die -= CYCLE_DELTA;
			vm->arena.check_count = 0;
		}
		else
			vm->arena.check_count++;
		vm->arena.cycle_since_check = 0;
		vm->arena.lives_since_last_check = 0;
		i = vm->nbr_champ;
		while (i--)
			vm->champs[i].lives_since_last_check = 0;
	}
}
