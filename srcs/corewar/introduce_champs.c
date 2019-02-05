/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_champs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 08:57:23 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/30 11:37:50 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		introduce_champs(t_vm vm)
{
	int		no;

	no = -1;
	ft_printf("Introducing contestants...\n");
	while (++no < vm.nbr_champ)
		ft_printf("Player %d, weighing %d bytes, %s (\"%s\") !\n",\
			vm.champs[no].number,\
			vm.champs[no].code.header.prog_size,\
			vm.champs[no].code.header.prog_name,\
			vm.champs[no].code.header.comment);
}
