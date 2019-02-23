/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:42:46 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/21 18:13:58 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			parse_sounds(t_vm *vm, char **argv, int index)
{
	if (!ft_strcmp(argv[index], "-sounds"))
	{
		vm->sounds = 1;
		return (1);
	}
	return (0);
}

int			parse_dump(t_vm *vm, char **argv, int argc, int index)
{
	if (!ft_strcmp(argv[index], "-dump"))
	{
		index++;
		if (index < argc)
			vm->dump = ft_atoi(argv[index]);
		if (vm->dump < 1)
			error_exit(vm, "Wrong dump value.");
		return (1);
	}
	return (0);
}

int			parse_n(t_vm *vm, char **argv, int index)
{
	if (!ft_strcmp(argv[index], "-n"))
	{
		index++;
		vm->n = ft_atoi(argv[index]);
		if (vm->n < 1)
			error_exit(vm, "Wrong player number value.");
		index++;
		read_champ(vm, argv, index, 1);
		return (1);
	}
	return (0);
}

int			parse_visu(t_vm *vm, char **argv, int index)
{
	if (!ft_strcmp(argv[index], "-visu"))
	{
		vm->visu = 1;
		return (1);
	}
	return (0);
}

char		**parse_command(t_vm *vm, char **argv, int argc, int index)
{
	char **new_pos;

	new_pos = argv;
	if (index >= argc)
		return (argv);
	else if (vm->nbr_champ == MAX_PLAYERS)
		error_exit(vm, "Too many players!");
	else if (parse_dump(vm, argv, argc, index))
		index += 2;
	else if (parse_sounds(vm, argv, index))
		index += 1;
	else if (parse_n(vm, argv, index))
		index += 3;
	else if (parse_visu(vm, argv, index))
		index++;
	else if (argv[index][0] == '-')
		error_exit(vm, "Not a valid option.");
	else if (index < argc)
	{
		read_champ(vm, argv, index, 0);
		index += 1;
	}
	else
		return (new_pos);
	return (parse_command(vm, new_pos, argc, index));
}
