/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:42:46 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/24 18:24:03 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			parse_dump(t_vm *vm, char **argv)
{
	if (ft_strcmp(*argv, "-dump"))
	{
		argv++;
		vm->dump = ft_atoi(*argv);
		if (vm->dump < 1)
			error_exit(vm, "Wrong dump value.");
		return (1);
	}
	return (0);
}

int			parse_numb(t_vm *vm, char **argv)
{
	if (ft_strcmp(*argv, "-n"))
	{
		argv++;
		vm->dump = ft_atoi(*argv);
		if (vm->n < 1)
			error_exit(vm, "Wrong player number value.");
		read_champ(vm, argv);
		vm->nbr_champ++;
		return (1);
	}
	return (0);
}

char		**parse_command(t_vm *vm, char **argv)
{
	char **new_pos;

	if (!(*argv))
		return (argv);
	else if (parse_dump(vm, argv))
		new_pos = argv + 2;
	else if (parse_numb(vm, argv))
		new_pos = argv + 2;
	else if (*argv)
	{
		read_champ(vm, argv);
		new_pos = argv + 1;
		vm->nbr_champ++;
	}
	else
		return (new_pos);
	return (parse_command(vm, new_pos));
}
