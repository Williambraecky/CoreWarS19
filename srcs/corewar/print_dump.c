/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 09:23:11 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/05 10:02:28 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		print_dump(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if ((i == 0 || (i) % 32 == 0) && i != MEM_SIZE - 1)
			ft_printf("\n0x0%.3x : ", i);
		else
			ft_printf(" ");
		ft_printf("%.2x", vm->arena.arena[i]);
		i++;
	}
	ft_printf("\n");
}
