/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/27 11:21:22 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			issue(t_vm vm)
{
	if (vm.nbr_champ < 1)
		error_exit(&vm, "No champ in there arena! Cowards...");
	return (0);
}

void		time_for_battle(t_vm *vm, WINDOW **windows)
{
	int		index;

	vm->visu ? 0 : introduce_champs(*vm);
	while (vm->arena.nbr_process_alive && dump_check(*vm))
	{
		vm->visu ? reset_p_color(vm) : 0;
		(!vm->visu || vm->visu_pause) ? do_cycle(vm) : 1;
		vm->visu ? setup_p_color(vm) : 0;
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
	char	name[PROG_NAME_LENGTH];
	int		i;
	int		index;

	if (argc < 2)
		return (error_usage());
	ft_memset((void *)&vm, 0, sizeof(t_vm));
	init_vm(&vm);
	index = 1;
	argv = parse_command(&vm, argv, argc, index);
	issue(vm);
	i = PROG_NAME_LENGTH;
	while (i--)
		name[i] = vm.champs[0].code.header.prog_name[i];
	vm.visu ? init_visu(window) : 0;
	i = PROG_NAME_LENGTH;
	while (i--)
		vm.champs[0].code.header.prog_name[i] = name[i];
	prepare_battle(&vm);
	time_for_battle(&vm, window);
	vm.visu ? endwin() : 0;
	free_all(&vm);
}
