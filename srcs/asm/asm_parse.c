/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/25 17:11:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	parse_name_comment(t_asm *asm_t)
{
	char	*str;
	int		ret;
	char	*property;

	str = NULL;
	while ((ret = get_next_line(asm_t->fd, &str)) == 1 && ++(asm_t->line))
	{
		if (strtrimset(&str) == -1)
			exit_error(asm_t, "Out of memory");
		if (ft_strlen(str))
		{
			if (ft_strstartswith(str, ".name"))
				asm_t->champ.header.name = read_property(asm_t, str);
			else if (ft_strstartswith(str, ".comment"))
				;
		}
		free(str);
	}
	if (ret == -1)
		exit_error(asm_t, "could not read file");
	return (asm_t->has_name == 1 && asm_t->has_description == 1);
}

int			asm_parse(t_asm *asm_t)
{
	if (parse_name_comment(asm_t) == -1)
		return (-1);
	return (1);
}
