/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlabel_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:48:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 17:24:38 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		dlabel_of_type(char *line, size_t i)
{
	if (line[i] != DIRECT_CHAR || line[i + 1] != LABEL_CHAR)
		return (0);
	i += 2;
	while (line[i])
	{
		if (ft_strchr(SEPARATOR_CHARS, line[i]))
			break ;
		else if (!ft_strchr(LABEL_CHARS, line[i]))
			return (0);
		i++;
	}
	return (1);
}

t_token	dlabel_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = DIRECT_LABEL;
	j = i + 2;
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
