/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:32:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 18:13:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

int			instruction_of_type(char *line, size_t i)
{
	return (line[i] && line[i] != '\n');
}

t_token		instruction_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = INSTRUCTION;
	j = i;
	while (line[j] && !is_space(line[j]))
	{
		if (!ft_strchr(LABEL_CHARS, line[j]))
		{
			ret.type = LEX_ERROR;
			ret.pos = str_calc_pos(line, j);
			return (ret);
		}
		j++;
	}
	ret.string = ft_strsub(line, i, j - i);
	if (!ret.string)
		ret.type = MEM_ERROR;
	else
		ret.size = ft_strlen(ret.string);
	return (ret);
}

static int	type_is_param(t_type type)
{
	return (type == REGISTER
		|| type == DIRECT
		|| type == DIRECT_LABEL
		|| type == INDIRECT);
}

void		process_instruction(t_asm *asm_t, t_token token, size_t *i)
{
	t_op	*op;
	int		param_count;
	t_token	current;
	int		instruction_pos;

	(*i)++;
	op = get_op(token.string);
	if (!op)
		invalid_instruction_error(asm_t, token);
	instruction_pos = asm_t->champ.header.prog_size;
	code_write_byte(asm_t, op->op_code);
	if (op->code_octet)
		code_write_byte(asm_t, gen_code_octet(asm_t, *i));
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
	if (param_count != op->nb_arg)
		exit_error(asm_t, "Invalid number of parameters");
}
