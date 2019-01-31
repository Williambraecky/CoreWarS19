/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:53:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 15:16:03 by wbraeckm         ###   ########.fr       */
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

void	process_comment(t_asm *asm_t, t_token token, size_t *i)
{
	t_token	string_token;

	(*i)++;
	if (asm_t->flags & COMMENT_FLAG)
		syntax_error(asm_t, token);
	else if (asm_t->tokens[*i].type != STRING)
		syntax_error(asm_t, asm_t->tokens[*i]);
	asm_t->flags |= COMMENT_FLAG;
	string_token = asm_t->tokens[*i];
	if (asm_t->tokens[*i].size > COMMENT_LENGTH)
		asm_t->flags |= COMMENT_TOO_LONG;
	else
		ft_strncpy(asm_t->champ.header.comment,
			string_token.string + 1, string_token.size - 2);
	(*i)++;
}
