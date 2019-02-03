/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/03 14:18:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_champ(t_asm *asm_t, char *filename)
{
	int				fd;
	unsigned int	size;

	if (!filename)
		exit_error(asm_t, "Invalid file name");
	if (!(fd = open(filename, O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
		exit_error(asm_t, "Could not open file");
	ft_printf("Writing output program to %s\n", filename);
	size = asm_t->champ.header.prog_size;
	asm_t->champ.header.prog_size =
	reverse_int32(asm_t->champ.header.prog_size);
	if (write(fd, &asm_t->champ.header, sizeof(t_header)) == -1 ||
		write(fd, asm_t->code, size) == -1)
		exit_error(asm_t, "Error writing to file");
	if (close(fd) == -1)
		exit_error(asm_t, "Error closing file");
}

/*
** TODO: post process error handling (ex: name too long comment too long etc)
*/

int			main(int argc, char **argv)
{
	t_asm	asm_t;

	if (argc == 1)
	{
		ft_printf_fd(2, "Usage: %s <sourcefile.s>\n", argv[0]);
		exit(1);
	}
	ft_memset(&asm_t, 0, sizeof(asm_t));
	if ((asm_t.fd = open(argv[argc - 1], O_RDONLY)) == -1)
	{
		ft_printf_fd(2, "Can't read source file %s\n", argv[argc - 1]);
		exit(1);
	}
	asm_t.champ.header.magic = reverse_int32(COREWAR_EXEC_MAGIC);
	asm_parse(&asm_t);
	asm_token_parse(&asm_t);
	asm_replace_labels(&asm_t);
	write_champ(&asm_t, "test_file");
	free_asm(&asm_t);
	return (0);
}
