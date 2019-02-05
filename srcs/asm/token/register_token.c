/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:20:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/05 15:16:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		register_of_type(char *line, size_t i)
{
	size_t	j;

	if (line[i++] != 'r')
		return (0);
	if (!ft_isdigit(line[i++]))
		return (0);
	j = 1;
	while (line[i] && j < 4)
	{
		if (ft_strchr(SEPARATOR_CHARS, line[i]))
			break ;
		else if (!ft_isdigit(line[i]))
			return (0);
		i++;
		j++;
	}
	return (j >= 1 && j < 3);
}

t_token	register_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = REGISTER;
	j = i;
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

void	process_register(t_asm *asm_t, t_token token)
{
	t_u8	octet;
	size_t	i;

	octet = 0;
	i = 1;
	while (token.string[i])
	{
		octet *= 10;
		octet += token.string[i++] - '0';
	}
	code_write_byte(asm_t, octet);
}
