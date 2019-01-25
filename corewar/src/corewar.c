/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/25 17:09:51 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		main(int argc, char **argv)
{
	t_vm	*vm;

	if (argc < 2 || argc > 16)
		return (error_usage());
	vm = NULL;
	ft_memset((void *)vm, 0, sizeof(t_vm));
//	init_vm(vm);
	argv++;
	argv = parse_command(vm, argv);
//	check_error(vm);
//	time_for_battle(vm);
//	free_all(vm);
}
