/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:00:29 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 17:31:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		separator_of_type(char *line, size_t i)
{
	return (line[i] == ',');
}

t_token	separator_make_token(char *line, size_t i)
{
	t_token	ret;

	(void)line;
	(void)i;
	ret.type = SEPARATOR;
	ret.size = 1;
	ret.string = ft_strdup(",");
	if (!ret.string)
		ret.type = MEM_ERROR;
	return (ret);
}
