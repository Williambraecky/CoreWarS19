/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:45:41 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/18 14:01:32 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		error_arg(void)
{
	ft_printf("Error arguments\n");
	exit(0);
}

void		error_exit(t_vm *vm, char *msg)
{
	if (vm->visu)
		endwin();
	ft_printf("%s\n", msg);
	free_all(vm);
	exit(0);
}

int			error_usage(void)
{
	ft_printf("Usage: ./corewar [-dump nbr_cycles] [-visu] [-sounds] ");
	ft_printf("[[-n number] champion1.cor] ...\n\n");
	ft_printf("\t-dump nbr_cycles:\n\t\t\t\t");
	ft_printf("Dumps memory after nbr_cycles then exits\n");
	ft_printf("\t-visu\t\t:\n\t\t\t\t");
	ft_printf("Use the visual mode to display the battle, live.\n");
	ft_printf("\t-sounds\t\t:\n\t\t\t\t");
	ft_printf("Use sounds mode to add special effect to the battle.\n");
	ft_printf("\t-n number\t:\n\t\t\t\t");
	ft_printf("Set the number of the following champion to number.\n");
	return (0);
}
