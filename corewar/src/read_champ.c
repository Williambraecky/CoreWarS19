/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:54:06 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/01 20:32:00 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		parse_header(t_vm *vm, unsigned char *buff)
{
	unsigned int	magic;
	int				i;
	int				j;
	unsigned int	prog_size;

	magic = n_bytes_to_uint(buff, 4);
	if (magic != COREWAR_EXEC_MAGIC)
		error_exit(vm, "Error. Not a valid .cor file.");
	i = 4;
	j = 0;
	while (j < PROG_NAME_LENGTH)
		vm->champs[vm->nbr_champ].code.header.prog_name[j++] = buff[i++];
	if ((prog_size = n_bytes_to_uint(&(buff[i + 4]), 4)) > CHAMP_MAX_SIZE)
		error_exit(vm, "Error. Champion has too long code.");
	vm->champs[vm->nbr_champ].code.header.prog_size = prog_size;
	i += 8;
	j = 0;
	while (j < COMMENT_LENGTH)
		vm->champs[vm->nbr_champ].code.header.comment[j++] = buff[i++];
}

void		parse_code(t_vm *vm,  unsigned char *buff)
{
	int		i;
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

void		read_champ(t_vm *vm, char **argv, int mode)
{
	int				fd;
	t_champ			*champ;
	size_t			size_code;
	unsigned char	buff[16 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE];

	size_code = sizeof(t_code);
	champ = &vm->champs[vm->nbr_champ];
	champ->lives = 0;
	champ->lives_since_last_check = 0;
	if (mode)
		champ->number = vm->n;
	else
		champ->number = find_number(vm);
	if ((fd = open(*argv, O_RDONLY)) < 0)
		error_exit(vm, "Error reading file.");
	read(fd, buff, size_code);
	parse_header(vm, buff);
	parse_code(vm, &buff[PROG_NAME_LENGTH + COMMENT_LENGTH + 8]);
	vm->nbr_champ++;
}
