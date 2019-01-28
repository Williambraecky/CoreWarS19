/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:32:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 15:37:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

int			instruction_of_type(char *line, size_t i)
{
	return (line[i] && line[i] != '\n');
}

t_token		instruction_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = INSTRUCTION;
	j = i;
	while (line[j] && !is_space(line[j]))
		j++;
	ret.string = ft_strsub(line, i, j - i);
	if (!ret.string)
		ret.type = MEM_ERROR;
	else
		ret.size = ft_strlen(ret.string);
	return (ret);
}
