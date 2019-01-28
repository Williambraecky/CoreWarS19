/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:33:42 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 18:34:01 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		direct_of_type(char *line, size_t i)
{
	if (line[i] != DIRECT_CHAR)
		return (0);
	i++;
	if (line[i] == '-')
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

t_token	direct_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = DIRECT;
	j = i + 1;
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
		ret.size = ft_strlen(ret.string);
	return (ret);
}