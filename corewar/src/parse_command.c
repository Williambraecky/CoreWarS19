/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:42:46 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/29 16:38:35 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			parse_dump(t_vm *vm, char **argv)
{
	if (!ft_strcmp(*argv, "-dump"))
	{
		argv++;
		vm->dump = n_bytes_to_uint((unsigned char *) argv, 4);
		if (vm->dump < 1)
			error_exit(vm, "Wrong dump value.");
		return (1);
	}
	return (0);
}

int			parse_n(t_vm *vm, char **argv)
{
	if (!ft_strcmp(*argv, "-n"))
	{
		argv++;
		vm->n = ft_atoi(*argv);
		if (vm->n < 1)
			error_exit(vm, "Wrong player number value.");
		argv++;
		read_champ(vm, argv, 1);
		return (1);
	}
	return (0);
}

char		**parse_command(t_vm *vm, char **argv)
{
	char **new_pos;

	new_pos = argv;
	if (!(*argv) &&  printf("1\n"))
		return (argv);
	else if (vm->nbr_champ == MAX_PLAYERS && printf("2\n"))
		error_exit(vm, "Too many players!");
	else if (parse_dump(vm, argv) && printf("3\n"))
		new_pos = argv + 2;
	else if (parse_n(vm, argv) && printf("4\n"))
		new_pos = argv + 3;
	else if (*argv && printf("5\n"))
	{
		read_champ(vm, argv, 0);
		new_pos = argv + 1;
	}
	else if (printf("6\n"))
		return (new_pos);
	return (parse_command(vm, new_pos));
}
