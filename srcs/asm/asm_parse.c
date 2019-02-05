/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/05 14:59:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_define	g_def_table[] =
{
	{COMMAND_NAME, name_of_type, name_make_token},
	{COMMAND_COMMENT, comment_of_type, comment_make_token},
	{SEPARATOR, separator_of_type, separator_make_token},
	{STRING, string_of_type, string_make_token},
	{LABEL, label_of_type, label_make_token},
	{REGISTER, register_of_type, register_make_token},
	{DIRECT, direct_of_type, direct_make_token},
	{DIRECT_LABEL, dlabel_of_type, dlabel_make_token},
	{INDIRECT, indirect_of_type, indirect_make_token},
	{INDIRECT_LABEL, ilabel_of_type, ilabel_make_token},
	{INSTRUCTION, instruction_of_type, instruction_make_token},
	{ENDLINE, endline_of_type, endline_make_token},
	{END, end_of_type, end_make_token},
	{LEX_ERROR, NULL, NULL}
};

static t_token	get_next_token(char *line, size_t i)
{
	size_t	j;

	j = 0;
	while (g_def_table[j].type != LEX_ERROR)
	{
		if (g_def_table[j].is_of_type(line, i))
			return (g_def_table[j].make_token(line, i));
		j++;
	}
	return ((t_token){.type = LEX_ERROR, .string = NULL,
		.pos = str_calc_pos(line, i)});
}

static void		handle_error(t_asm *asm_t, t_token token)
{
	if (token.type == LEX_ERROR)
		lexical_error(asm_t, token.pos);
	exit_error(asm_t, "Out of memory");
}

static void		skip_comments(t_asm *asm_t, size_t *i)
{
	if (*i >= (size_t)asm_t->file_size ||
		(asm_t->file[*i] != '#' && asm_t->file[*i] != ';'))
		return ;
	while (asm_t->file[*i] && asm_t->file[*i] != '\n')
		(*i)++;
}

void			asm_parse(t_asm *asm_t)
{
	size_t	i;
	t_token	current;

	gnl_to_one_string(asm_t);
	i = first_non_space(asm_t->file) - asm_t->file;
	while (i < (size_t)asm_t->file_size)
	{
		skip_comments(asm_t, &i);
		current = get_next_token(asm_t->file, i);
		if (current.type != LEX_ERROR)
			current.pos = str_calc_pos(asm_t->file, i);
		asm_add_token(asm_t, current);
		if (current.type == LEX_ERROR || current.type == MEM_ERROR)
			handle_error(asm_t, current);
		i += current.size;
		if (current.type == END)
			break ;
		if (i < (size_t)asm_t->file_size)
			i += first_non_space(asm_t->file + i) - (asm_t->file + i);
	}
	asm_add_token(asm_t, (t_token){.type = END,
		.string = NULL, .pos = str_calc_pos(asm_t->file, i)});
}
