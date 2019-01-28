/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:11:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 12:23:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Maybe max file size?
*/

void	gnl_to_one_string(t_asm *asm_t)
{
	char	buffer[ASM_BUFFER_SIZE + 1];
	char	*new;
	int		ret;

	if (asm_t->file)
		ft_strdel(&asm_t->file);
	while ((ret = read(asm_t->fd, buffer, ASM_BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (asm_t->file)
			new = ft_strjoin(asm_t->file, buffer);
		else
			new = ft_strdup(buffer);
		if (!new)
			exit_error(asm_t, "Out of memory");
		asm_t->file_size += ret;
		ft_strdel(&asm_t->file);
		asm_t->file = new;
	}
	if (ret == -1)
		exit_error(asm_t, "Error while reading file");
}
