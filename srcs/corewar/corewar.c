/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/05 15:15:18 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		time_for_battle(t_vm *vm, WINDOW **windows)
{
	int		index;

	vm->visu ? 0 : introduce_champs(*vm);
	while (vm->arena.nbr_process_alive)
	{
		vm->visu_pause == 0 ? do_cycle(vm) : 1;
		vm->visu ? print_visu(vm, windows, 1) : 0;
	}
	index = vm->arena.winner;
	if (vm->dump != -1)
		return (print_dump(vm));
	if (index == -1 && !vm->visu)
		ft_printf("No winner as no contestant did a live.\n");
	else if (!vm->visu && play_victory(vm))
		ft_printf("Player %d (%s) won!\n", vm->champs[index].number,\
			vm->champs[index].code.header.prog_name);
	else if (play_victory(vm))
		print_visu(vm, windows, 0);
}

int			main(int argc, char **argv)
{
	t_vm	vm;
	WINDOW	*window[5];

	if (argc < 2)
		return (error_usage());
	ft_memset((void *)&vm, 0, sizeof(t_vm));
	init_vm(&vm);
	argv++;
	argv = parse_command(&vm, argv);
	prepare_battle(&vm);
	vm.visu ? init_visu(window) : 0;
	time_for_battle(&vm, window);
	vm.visu ? endwin() : 0;
	free_all(&vm);
}
