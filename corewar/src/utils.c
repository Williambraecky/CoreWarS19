/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:56:23 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/30 10:49:02 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				find_number(t_vm *vm)
{
	char	list[MAX_PLAYERS];
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		list[i] = 0;
	i = -1;
	while (++i < vm->nbr_champ)
		if (vm->champs[i].number <= MAX_PLAYERS)
			list[vm->champs[i].number - 1] = 1;
	i = -1;
	while (++i < MAX_PLAYERS)
		if (list[i] == 0)
			return (i + 1);
	error_exit(vm, "Too many players.");
	return (1);
}

unsigned int	n_bytes_to_uint(unsigned char *header, unsigned int nbr)
{
	int					i;
	unsigned int		ret;
	unsigned int		mask;

	ret = 0;
	if (nbr > 4)
		exit (0);
	i = -1;
	while (++i < nbr)
	{
		ret = ret << 8;
		mask = (unsigned int)*header;
		ret = ret | mask;
		header++;
	}
	return (ret);
}

int				dump_check(t_vm vm)
{
	if (vm.dump < 0)
		return (1);
	else if (vm.arena.total_cycle < vm.dump)
		return (1);
	else
		return (0);
}
