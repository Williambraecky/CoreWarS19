/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:39:06 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 18:51:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Functions related to END type
*/

int		end_of_type(char *line, size_t i)
{
	return (line[i] == '\0');
}

t_token	end_make_token(char *line, size_t i)
{
	t_token	ret;

	(void)line;
	(void)i;
	ret.type = END;
	ret.string = ft_strdup("");
	if (ret.string == NULL)
		ret.type = MEM_ERROR;
	return (ret);
}
