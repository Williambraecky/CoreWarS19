/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:20:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 17:19:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		register_of_type(char *line, size_t i)
{
	if (line[i] != 'r')
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
		ret.size = ft_strlen(ret.string);
	return (ret);
}
