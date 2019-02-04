/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indirect_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:27:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 16:50:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		indirect_of_type(char *line, size_t i)
{
	if (line[i] == '-')
		i++;
	if (!ft_isdigit(line[i]))
		return (0);
	i++;
	while (line[i])
	{
		if (ft_strchr(SEPARATOR_CHARS, line[i]))
			break ;
		else if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

t_token	indirect_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = INDIRECT;
	j = i;
	if (line[j] == '-')
		j++;
	while (line[j])
	{
		if (ft_strchr(SEPARATOR_CHARS, line[j]))
			break ;
		j++;
	}
	ret.string = ft_strsub(line, i, j - i);
	if (!ret.string)
		ret.type = MEM_ERROR;
	else
		ret.size = j - i;
	return (ret);
}

void	process_indirect(t_asm *asm_t, t_token token)
{
	short	s;

	s = (short)ft_atoi(token.string);
	code_write_bytes(asm_t, (t_u8*)&s, 2);
}
