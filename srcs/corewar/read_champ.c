/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:54:06 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 15:46:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		parse_header(t_vm *vm, t_u8 *buff)
{
	t_u32	magic;
	int		i;
	int		j;
	t_u32	prog_size;

	magic = n_bytes_to_uint(buff, 4);
	if (magic != COREWAR_EXEC_MAGIC)
		error_exit(vm, "Error: not a valid .cor file.");
	i = 4;
	j = 0;
	while (j < PROG_NAME_LENGTH)
		vm->champs[vm->nbr_champ].code.header.prog_name[j++] = buff[i++];
	vm->champs[vm->nbr_champ].code.header.prog_name[j] = 0;
	if ((prog_size = n_bytes_to_uint(&(buff[i + 4]), 4)) > CHAMP_MAX_SIZE)
		error_exit(vm, "Error: champion has too long code.");
	vm->champs[vm->nbr_champ].code.header.prog_size = prog_size;
	i += 8;
	j = 0;
	while (j < COMMENT_LENGTH)
		vm->champs[vm->nbr_champ].code.header.comment[j++] = buff[i++];
}

void		parse_code(t_vm *vm, t_u8 *buff)
{
	t_u32	i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < vm->champs[vm->nbr_champ].code.header.prog_size && buff[i] == 0)
		i++;
	k = i;
	while (i < vm->champs[vm->nbr_champ].code.header.prog_size + k)
		vm->champs[vm->nbr_champ].code.prog[j++] = buff[i++];
}

void		read_champ(t_vm *vm, char **argv, int index, int mode)
{
	int		fd;
	t_champ	*champ;
	size_t	size_code;
	t_u8	bf[16 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE];

	size_code = sizeof(t_header);
	champ = &vm->champs[vm->nbr_champ];
	champ->lives = 0;
	champ->lives_since_last_check = 0;
	if (mode)
		champ->number = vm->n;
	else
		champ->number = find_number(vm);
	if ((fd = open(argv[index], O_RDONLY)) < 0)
		error_exit(vm, "Error: can't read source file.");
	if ((read(fd, bf, size_code) != sizeof(bf) - CHAMP_MAX_SIZE))
		error_exit(vm, "Error: file too small to be a valide .cor file.");
	parse_header(vm, bf);
	size_code = CHAMP_MAX_SIZE;
	if (read(fd, bf, size_code + 1) != champ->code.header.prog_size)
		error_exit(vm, "Error: code size differs from what its header says.");
	parse_code(vm, bf);
	vm->nbr_champ++;
}
