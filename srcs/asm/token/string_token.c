/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:05:18 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/21 13:57:49 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		string_of_type(char *line, size_t i)
{
	return (line[i] == '\"');
}

t_token	string_make_token(char *line, size_t i)
{
	t_token	ret;
	char	*end;

	ret.type = STRING;
	end = ft_strchr(line + i + 1, '\"');
	if (end != NULL)
	{
		ret.string = ft_strsub(line, i, (end + 1) - (line + i));
		if (!ret.string)
			ret.type = MEM_ERROR;
		else
			ret.size = ft_strlen(ret.string);
	}
	else
	{
		ret.string = NULL;
		ret.size = 0;
		ret.type = LEX_ERROR;
	}
	return (ret);
}
