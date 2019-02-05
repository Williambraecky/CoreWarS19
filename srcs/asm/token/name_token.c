/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:53:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/03 15:58:10 by wbraeckm         ###   ########.fr       */
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

void	process_name(t_asm *asm_t, t_token token, size_t *i)
{
	t_token	string;

	if (asm_t->flags & NAME_FLAG)
		syntax_error(asm_t, token);
	else if (asm_t->tokens[*i + 1].type != STRING)
		syntax_error(asm_t, asm_t->tokens[*i + 1]);
	(*i)++;
	asm_t->flags |= NAME_FLAG;
	string = asm_t->tokens[*i];
	if (asm_t->tokens[*i].size > PROG_NAME_LENGTH
		&& !(asm_t->flags & COMMENT_TOO_LONG))
		asm_t->flags |= NAME_TOO_LONG;
	else
		ft_strncpy(asm_t->champ.header.prog_name,
			string.string + 1, ft_min(string.size - 2, PROG_NAME_LENGTH));
	(*i)++;
}
