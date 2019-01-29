/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_battle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 10:20:28 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/29 16:46:52 by sde-spie         ###   ########.fr       */
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
	int		i;

	i = -1;
	ft_printf("nbrchamp = %d\n", vm->nbr_champ);
	while (++i < vm->nbr_champ)
	{
		vm->arena.process[i] = *create_process(vm);
		printf("post create process\n");
		vm->arena.process[i].index_champ = vm->champs[i].number;
		vm->arena.process[i].registre[0] = vm->champs[i].number;
		vm->arena.process[i].index_arena = (i * MEM_SIZE / vm->nbr_champ);
		printf("end champ %d\n", i);
	}
}

void			paste_memory(t_vm *vm)
{
	int		i;
	int		j;
	int		start_index;

	i = -1;
	while (++i < MEM_SIZE)
		vm->arena.arena[i] = 0;
	i = -1;
	while (++i < vm->nbr_champ)
	{
		start_index = (i * MEM_SIZE / vm->nbr_champ);
		j = -1;
		while (++j < vm->champs[i].code.header.prog_size)
			vm->arena.arena[i + start_index] = vm->champs[i].code.prog[j];
	}
}

void			prepare_battle(t_vm *vm)
{
	order_champs(vm);
	check_error(vm);
	init_process(vm);
	paste_memory(vm);
}
