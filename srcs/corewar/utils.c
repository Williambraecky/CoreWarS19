/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:56:23 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:37:06 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				find_number(t_vm *vm)
{
	char	list[MAX_PLAYERS];
	int		i;

	i = MAX_PLAYERS;
	while (i--)
		list[i] = 0;
	i = vm->nbr_champ;
	while (i--)
		if (vm->champs[i].number <= MAX_PLAYERS)
			list[vm->champs[i].number - 1] = 1;
	i = 0;
	while (i < MAX_PLAYERS)
		if (list[i++] == 0)
			return (i);
	error_exit(vm, "Error: too many players.");
	return (1);
}

int				dump_check(t_vm vm)
{
	if (vm.dump < 0)
		return (1);
	else if (vm.arena.total_cycle < vm.dump)
		return (1);
	return (0);
}

void			lit_end_tovm(t_vm *vm, int pc, int value, int champ_index)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		vm->arena.arena[(pc + i) % MEM_SIZE] = (value >> (24 - i * 8)) & 0xFF;
		vm->arena.arena_owner[(pc + i) % MEM_SIZE] = -1 * champ_index;
		i++;
	}
}

int				mod(int value)
{
	if (value < 0)
		return (MEM_SIZE + (value % MEM_SIZE));
	return (value % MEM_SIZE);
}
