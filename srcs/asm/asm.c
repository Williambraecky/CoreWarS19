/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/26 16:03:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_champ(t_asm *asm_t, char *filename)
{
	int fd;

	if (!filename)
		exit_error(asm_t, "Invalid file name");
	if (!(fd = open(filename, O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
		exit_error(asm_t, "Could not open file");
	ft_printf("Writing output program to %s\n", filename);
	if (write(fd, &asm_t->champ,
		sizeof(t_header) + reverse_int32(asm_t->champ.header.prog_size)) == -1)
		exit_error(asm_t, "Error writing to file");
	if (close(fd) == -1)
		exit_error(asm_t, "Error closing file");
}

int			main(int argc, char **argv)
{
	t_asm	asm_t;

	if (argc == 1)
		exit_usage(argv[0]);
	ft_memset(&asm_t, 0, sizeof(asm_t));
	if ((asm_t.fd = open(argv[argc - 1], O_RDONLY)) == -1)
	{
		ft_printf_fd(2, "Can't read source file %s\n", argv[argc - 1]);
		exit(0);
	}
	ft_printf("Slt c l'asm\n");
	asm_t.champ.header.magic = reverse_int32(COREWAR_EXEC_MAGIC);
	asm_parse(&asm_t);
	write_champ(&asm_t, "test_file");
	(void)argc;
	(void)argv;
	return (0);
}
