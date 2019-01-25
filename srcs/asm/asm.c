/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/25 13:33:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_champ	champ;
	int		fd;

	ft_printf("Slt c l'asm\n");
	ft_memset(&champ, 0, sizeof(champ));
	fd = open("test", O_RDWR | O_CREAT);
	champ.header.magic = reverse_int32(COREWAR_EXEC_MAGIC);
	ft_strcpy(champ.header.prog_name, "CHAMPION 19");
	champ.header.prog_size = reverse_int32(CHAMP_MAX_SIZE);
	champ.code[0] = 0xFF;
	ft_strcpy(champ.header.comment, "JE SUIS UN COMMENTAIRE FDP");
	write(fd, &champ, sizeof(t_header) + reverse_int32(champ.header.prog_size));
	close(fd);
	(void)argc;
	(void)argv;
	return (0);
}
