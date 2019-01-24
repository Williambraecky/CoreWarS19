/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:45:41 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/24 18:04:08 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		error_arg(void)
{
	ft_printf("Error arguments\n");
	exit ();
}

void		error_exit(t_vm *vm, char *msg)
{
	ft_printf("%d\n", msg);
	free_all(vm);
	exit ();
}
