/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_battle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 10:20:28 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:45:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			check_error(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->nbr_champ - 1)
	{
		if (vm->champs[i].number == vm->champs[i + 1].number)
			error_exit(vm, "Error: same numbers assigned to multiple Champs.");
	}
}

void			order_champs(t_vm *vm)
{
	int		i;
	int		j;
	t_champ	tmp;

	i = -1;
	while (++i < vm->nbr_champ)
	{
		j = i;
		while (++j < vm->nbr_champ)
			if (vm->champs[i].number > vm->champs[j].number)
			{
				tmp = vm->champs[i];
				vm->champs[i] = vm->champs[j];
				vm->champs[j] = tmp;
			}
	}
}

void			init_process(t_vm *vm)
{
	int			i;
	t_process	*pro;

	i = -1;
	vm->arena.process = (t_process *)malloc(sizeof(t_process) * NBR_PROCESS);
	vm->arena.s_proc = NBR_PROCESS;
	pro = vm->arena.process;
	while (++i < vm->nbr_champ)
	{
		set_process(vm, &vm->arena.process[i]);
		pro[i].index_champ = i + 1;
		pro[i].registre[1] = vm->champs[i].number;
	}
}

void			paste_memory(t_vm *vm)
{
	int		i;
	t_u32	j;
	int		start_index;

	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->arena.arena[i] = 0;
		vm->arena.arena_owner[i] = 5;
	}
	i = -1;
	while (++i < vm->nbr_champ)
	{
		start_index = (i * MEM_SIZE / vm->nbr_champ);
		vm->arena.process[i].pc = start_index;
		j = 0;
		while (j < vm->champs[i].code.header.prog_size)
		{
			vm->arena.arena[j + start_index] = vm->champs[i].code.prog[j];
			vm->arena.arena_owner[j + start_index] = i + 1;
			j++;
		}
	}
}

void			prepare_battle(t_vm *vm)
{
	order_champs(vm);
	check_error(vm);
	init_process(vm);
	paste_memory(vm);
}
