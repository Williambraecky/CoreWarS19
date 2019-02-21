/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:32:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/21 14:01:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			instruction_of_type(char *line, size_t i)
{
	return (line[i] && ft_strchr(LABEL_CHARS, line[i]) != NULL);
}

t_token		instruction_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = INSTRUCTION;
	j = i;
	while (line[j] && !(line[j] == ' ' || line[j] == '\n' ||
		line[j] == '\t' || line[j] == '\r' || line[j] == ','))
	{
		if (!ft_strchr(LABEL_CHARS, line[j]))
			break ;
		j++;
	}
	ret.string = ft_strsub(line, i, j - i);
	if (!ret.string)
		ret.type = MEM_ERROR;
	else
		ret.size = j - i;
	return (ret);
}

static int	type_is_param(t_type type)
{
	return (type == REGISTER
		|| type == DIRECT
		|| type == DIRECT_LABEL
		|| type == INDIRECT
		|| type == INDIRECT_LABEL);
}

static int	process_instruction_args(t_asm *asm_t, t_op *op, size_t *i,
	int instruction_pos)
{
	int		param_count;
	t_token	current;

	param_count = 0;
	while (type_is_param(asm_t->tokens[*i].type))
	{
		current = asm_t->tokens[*i];
		if (!instruction_check_param(op, current, param_count))
			invalid_parameter_type_error(asm_t, param_count,
				current.type, op->name);
		process_parameter(asm_t, current, op->label_size, instruction_pos);
		(*i)++;
		param_count++;
		if (asm_t->tokens[*i].type != SEPARATOR)
			break ;
		(*i)++;
	}
	if (asm_t->tokens[*i].type != ENDLINE)
		syntax_error(asm_t, asm_t->tokens[*i]);
	return (param_count);
}

void		process_instruction(t_asm *asm_t, t_token token, size_t *i)
{
	t_op	*op;
	int		instruction_pos;

	if (!(asm_t->flags & NAME_FLAG) || !(asm_t->flags & COMMENT_FLAG))
		syntax_error(asm_t, token);
	(*i)++;
	op = get_op(token.string);
	if (!op)
		invalid_instruction_error(asm_t, token);
	instruction_pos = asm_t->champ.header.prog_size;
	code_write_byte(asm_t, op->op_code);
	if (op->code_octet)
		code_write_byte(asm_t, gen_code_octet(asm_t, *i));
	if (process_instruction_args(asm_t, op, i, instruction_pos) != op->nb_arg)
	{
		ft_printf_fd(1, "Invalid parameter count for instruction %s\n",
			op->name);
		free_asm(asm_t);
		exit(1);
	}
}
