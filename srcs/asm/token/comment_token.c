/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:53:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 17:30:41 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		comment_of_type(char *line, size_t i)
{
	return (ft_strstartswith(line + i, ".comment"));
}

t_token	comment_make_token(char *line, size_t i)
{
	t_token	ret;

	(void)line;
	(void)i;
	ret.type = COMMAND_COMMENT;
	ret.size = 8;
	ret.string = ft_strdup(".comment");
	if (!ret.string)
		ret.type = MEM_ERROR;
	return (ret);
}
