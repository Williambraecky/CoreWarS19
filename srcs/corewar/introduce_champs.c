/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_champs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 08:57:23 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:31:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		introduce_champs(t_vm vm)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm.nbr_champ)
	{
		ft_printf("Player %d, weighing %d bytes, %s (\"%s\") !\n",\
			vm.champs[i].number,\
			vm.champs[i].code.header.prog_size,\
			vm.champs[i].code.header.prog_name,\
			vm.champs[i].code.header.comment);
		i++;
	}
}
