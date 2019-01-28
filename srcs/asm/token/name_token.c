/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:53:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 13:57:51 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		name_of_type(char *line, size_t i)
{
	return (ft_strstartswith(line + i, ".name"));
}

t_token	name_make_token(char *line, size_t i)
{
	t_token	ret;

	(void)line;
	(void)i;
	ret.type = COMMAND_NAME;
	ret.size = 5;
	ret.string = ft_strdup(".name");
	if (!ret.string)
		ret.type = MEM_ERROR;
	return (ret);
}
