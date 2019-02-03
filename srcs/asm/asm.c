/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/03 16:26:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_champ(t_asm *asm_t)
{
	int				fd;
	unsigned int	size;

	if (!asm_t->filename)
		exit_error(asm_t, "Out of memory");
	if (!(fd = open(asm_t->filename, O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
		exit_error(asm_t, "Could not open file");
	ft_printf("Writing output program to %s\n", asm_t->filename);
	size = asm_t->champ.header.prog_size;
	asm_t->champ.header.prog_size =
	reverse_int32(asm_t->champ.header.prog_size);
	if (write(fd, &asm_t->champ.header, sizeof(t_header)) == -1 ||
		write(fd, asm_t->code, size) == -1)
		exit_error(asm_t, "Error writing to file");
	if (close(fd) == -1)
		exit_error(asm_t, "Error closing write file");
}

static char	*gen_filename(char *orig_file)
{
	if (!ft_strstr(orig_file, ".s"))
		return (ft_strdup(".cor"));
	return (ft_strsrepl(orig_file, ".s", ".cor"));
}

static void	check_data(t_asm *asm_t)
{
	if (asm_t->flags & NAME_TOO_LONG)
	{
		ft_printf_fd(2, "Champion name too long (Max length %d)\n",
			PROG_NAME_LENGTH);
		free_asm(asm_t);
		exit(1);
	}
	else if (asm_t->flags & COMMENT_TOO_LONG)
	{
		ft_printf_fd(2, "Champion comment too long (Max length %d)\n",
			COMMENT_LENGTH);
		free_asm(asm_t);
		exit(1);
	}
}

/*
** TODO: Write to correct file
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
	check_data(&asm_t);
	asm_t.filename = gen_filename(argv[argc - 1]);
	write_champ(&asm_t);
	if (close(asm_t.fd) == -1)
		exit_error(&asm_t, "Error closing read file");
	free_asm(&asm_t);
	return (0);
}
