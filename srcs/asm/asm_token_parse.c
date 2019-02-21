/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_token_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:47:45 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/21 14:22:27 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	can_start_with_type(t_type type)
{
	return (type == COMMAND_NAME
		|| type == COMMAND_COMMENT
		|| type == LABEL
		|| type == INSTRUCTION);
}

static void	process_token(t_asm *asm_t, t_token token, size_t *i)
{
	if (token.type == COMMAND_NAME)
		process_name(asm_t, token, i);
	else if (token.type == COMMAND_COMMENT)
		process_comment(asm_t, token, i);
	else if (token.type == LABEL)
		process_label(asm_t, token, i);
	else
		process_instruction(asm_t, token, i);
	if ((token.type != LABEL && asm_t->tokens[*i].type != ENDLINE)
	|| (token.type == LABEL && asm_t->tokens[*i].type == LABEL))
		syntax_error(asm_t, asm_t->tokens[*i]);
}

void		asm_token_parse(t_asm *asm_t)
{
	size_t	i;
	t_token	current;

	i = 0;
	while (asm_t->tokens[i].type != END)
	{
		current = asm_t->tokens[i];
		if (can_start_with_type(current.type))
			process_token(asm_t, current, &i);
		else if (current.type != ENDLINE && current.type != END)
			syntax_error(asm_t, current);
		else
			i++;
	}
	if (!(asm_t->flags & NAME_FLAG) || !(asm_t->flags & COMMENT_FLAG)
		|| !asm_t->code)
	{
		asm_t->flags |= END_SYNTAX_ERR;
		syntax_error(asm_t, asm_t->tokens[i]);
	}
}
