/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:33:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/29 16:43:15 by sde-spie         ###   ########.fr       */
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
		int i = -1;
		while (++i < vm.champs[players].code.header.prog_size)
		{
			ft_putnbr(vm.champs[players].code.prog[i]);
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
		if (i % 32 == 0)
		ft_printf("\n");
	}
}

void		time_for_battle(t_vm *vm)
{
	
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc < 2 || argc > 16)
		return (error_usage());
	ft_memset((void *)&vm, 0, sizeof(t_vm));
//	init_vm(&vm);
	argv++;
	argv = parse_command(&vm, argv);
	prepare_battle(&vm);
	print_champs(vm);
//	print_memory(vm);
//	time_for_battle(&vm);
//	free_all(vm);
}
