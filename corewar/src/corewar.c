/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/04 15:52:04 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
/*
void		print_champs(t_vm vm)
{
	int	players;

	printf("____________________________\n");
	players = -1;
	while (++players < vm.nbr_champ)
	{
		printf("Champ number = %d\n", vm.champs[players].number);
		printf("Champ name = %s\n", vm.champs[players].code.header.prog_name);
		printf("Champ comment = %s\n", vm.champs[players].code.header.comment);
		printf("Champ size = %d\n", vm.champs[players].code.header.prog_size);
		unsigned int i = 0;
		while (i < vm.champs[players].code.header.prog_size)
		{
			ft_putnbr(vm.champs[players].code.prog[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
		printf("____________________________\n");
	}
}

void		print_memory2(t_vm vm)
{
	int i = -1;

	while (++i < MEM_SIZE)
	{
		ft_printf("%.2x ", vm.arena.arena[i]);
		if ((i + 1) % 64 == 0)
		ft_printf("\n");
	}
}

void		print_process(t_vm vm)
{
	int	i = 0;
	printf("print process = %d\n", vm.arena.nbr_process );
	while (i < vm.arena.nbr_process)
	{
		printf("index champ = %d\n", vm.arena.process[i].index_champ);
		printf("index arena = %ld\n", vm.arena.process[i].index_arena);
		printf("number = %d\n", vm.arena.process[i].number);
		printf("registre[0] = %d\n", vm.arena.process[i].registre[0]);
		printf("alive = %d\n", vm.arena.process[i++].alive);
		printf("_________\n");
	}
}*/

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
	if (index == -1 && !vm->visu)
		ft_printf("No winner as no contestant did a live.\n");
	else if (!vm->visu)
		ft_printf("Player %d (%s) won!\n", vm->champs[index].number,\
			vm->champs[index].code.header.prog_name);
	else
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
//	print_process(vm);
//	print_champs(vm);
//	print_memory2(vm);
	time_for_battle(&vm, window);
	ft_printf("taille = %ld\n", sizeof(vm));
	vm.visu ? endwin() : 0;
	free_all(&vm);
}
