/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/24 18:36:26 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2)
		return (error_usage());
	ft_memset(vm, 0, sizeof(t_vm);
	init_vm(mv);
	argv++;
	argv = parse_command(vm, argv);
	time_for_battle(vm);
	free_all(vm);
}
