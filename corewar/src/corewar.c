/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/30 14:28:40 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"


void	print_champs(t_vm vm)
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

void		print_memory(t_vm vm)
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
	while (i < vm.arena.nbr_process)
	{
		printf("index champ = %d\n", vm.arena.process[i].index_champ);
		printf("index arena = %ld\n", vm.arena.process[i].index_arena);
		printf("number = %d\n", vm.arena.process[i++].number);
	}

}

void		time_for_battle(t_vm *vm)
{
	int		index;

	introduce_champs(*vm);
	while (vm->arena.nbr_process_alive && dump_check(*vm))
		do_cycle(vm);
	index = vm->arena.winner;
	if (index == -1)
		ft_printf("No winner as no contestant did a live.\n");
	else
		ft_printf("Player %d (%s) won!\n", vm->champs[index].number,\
			vm->champs[index].code.header.prog_name);
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc < 2 || argc > 16)
		return (error_usage());
	ft_memset((void *)&vm, 0, sizeof(t_vm));
	init_vm(&vm);
	argv++;
	argv = parse_command(&vm, argv);
	prepare_battle(&vm);
//	print_process(vm);
//	print_champs(vm);
//	print_memory(vm);
	time_for_battle(&vm);
//	free_all(vm);
}
