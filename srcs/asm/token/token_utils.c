/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 12:34:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/21 14:06:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_type		g_type_table[] =
{
	MEM_ERROR,
	LEX_ERROR,
	ENDLINE,
	COMMAND_NAME,
	COMMAND_COMMENT,
	STRING,
	LABEL,
	INSTRUCTION,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	COMMENT,
	END
};

char		*g_string_table[] =
{
	"MEM_ERROR",
	"LEX_ERROR",
	"ENDLINE",
	"COMMAND_NAME",
	"COMMAND_COMMENT",
	"STRING",
	"LABEL",
	"INSTRUCTION",
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL",
	"SEPARATOR",
	"COMMENT",
	"END",
	NULL
};

/*
** find better way to avoid magic number
*/

char		*type_get_string(t_type type)
{
	size_t	i;

	i = 0;
	while (g_string_table[i])
	{
		if (g_type_table[i] == type)
			return (g_string_table[i]);
		i++;
	}
	return (NULL);
}

static void	ensure_enough_space(t_asm *asm_t)
{
	t_token	*new;
	size_t	new_size;

	if (asm_t->nb_tokens < asm_t->max_tokens)
		return ;
	if (TOKEN_SIZE_START == 0)
		exit_error(asm_t, "TOKEN_SIZE_START cannot be 0");
	if (asm_t->max_tokens == 0)
		new_size = TOKEN_SIZE_START;
	else
		new_size = asm_t->max_tokens * 2;
	if (!(new = (t_token *)ft_realloc(asm_t->tokens,
		asm_t->max_tokens * sizeof(t_token), new_size * sizeof(t_token))))
		exit_error(asm_t, "Out of memory");
	asm_t->max_tokens = new_size;
	asm_t->tokens = new;
}

void		asm_add_token(t_asm *asm_t, t_token token)
{
	ensure_enough_space(asm_t);
	asm_t->tokens[asm_t->nb_tokens++] = token;
}

static t_u8	get_param_code(t_token token)
{
	if (token.type == INDIRECT || token.type == INDIRECT_LABEL)
		return (IND_CODE);
	else if (token.type == DIRECT || token.type == DIRECT_LABEL)
		return (DIR_CODE);
	else if (token.type == REGISTER)
		return (REG_CODE);
	return (0);
}

t_u8		gen_code_octet(t_asm *asm_t, size_t pos)
{
	size_t	i;
	t_u8	octet;
	t_u8	current;

	i = 4;
	octet = 0;
	while (i--)
	{
		current = get_param_code(asm_t->tokens[pos++]);
		if (!current)
			break ;
		octet |= (current << (i * 2));
		if (asm_t->tokens[pos++].type != SEPARATOR)
			break ;
	}
	return (octet);
}
