/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_battle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 10:20:28 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/01 11:45:21 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			check_error(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->nbr_champ - 1)
	{
		if (vm->champs[i].number == vm->champs[i + 1].number)
			error_exit(vm, "Same numbers assigned to multiple Champions.");
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
	int			j;

	i = -1;
	vm->arena.process = (t_process *)malloc(sizeof(t_process) * NBR_PROCESS);
	pro = vm->arena.process;
	while (++i < vm->nbr_champ)
	{
		set_process(vm, &vm->arena.process[i]);
		pro[i].index_champ = vm->champs[i].number;
		pro[i].registre[0] = vm->champs[i].number;
	}
}

void			paste_memory(t_vm *vm)
{
	int		i;
	int		j;
	int		start_index;

	i = -1;
	while (++i < MEM_SIZE / 4)
		vm->arena.arena[i] = 0;
	i = -1;
	while (++i < vm->nbr_champ)
	{
		start_index = (i * MEM_SIZE / vm->nbr_champ);
		j = -1;
		while (++j < vm->champs[i].code.header.prog_size)
		{
			vm->arena.arena[j + start_index] = vm->champs[i].code.prog[j];
			vm->arena.arena_owner[j + start_index] = i;
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
