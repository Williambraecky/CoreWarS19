/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endline_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:26:00 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 15:27:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		endline_of_type(char *line, size_t i)
{
	return (line[i] == '\n');
}

t_token	endline_make_token(char *line, size_t i)
{
	t_token	ret;

	(void)line;
	(void)i;
	ret.type = ENDLINE;
	ret.string = ft_strdup("\n");
	if (!ret.string)
		ret.type = MEM_ERROR;
	else
		ret.size = 1;
	return (ret);
}
