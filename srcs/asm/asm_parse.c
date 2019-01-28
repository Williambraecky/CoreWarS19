/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 18:51:02 by wbraeckm         ###   ########.fr       */
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
	{INSTRUCTION, instruction_of_type, instruction_make_token},
	{ENDLINE, endline_of_type, endline_make_token},
	{END, end_of_type, end_make_token},
	{LEX_ERROR, NULL, NULL}
};

t_token		get_next_token(char *line, size_t i)
{
	size_t	j;

	j = 0;
	while (g_def_table[j].type != LEX_ERROR)
	{
		if (g_def_table[j].is_of_type(line, i))
			return (g_def_table[j].make_token(line, i));
		j++;
	}
	return ((t_token){.type = LEX_ERROR});
}

/*
** TODO: do this but with global tables in another file
*/

static char	*string_for_type(t_type type)
{
	if (type == MEM_ERROR)
		return ("MEM_ERROR");
	else if (type == LEX_ERROR)
		return ("LEX_ERROR");
	else if (type == ENDLINE)
		return ("ENDLINE");
	else if (type == COMMAND_NAME)
		return ("COMMAND_NAME");
	else if (type == COMMAND_COMMENT)
		return ("COMMAND_COMMENT");
	else if (type == STRING)
		return ("STRING");
	else if (type == LABEL)
		return ("LABEL");
	else if (type == INSTRUCTION)
		return ("INSTRUCTION");
	else if (type == REGISTER)
		return ("REGISTER");
	else if (type == DIRECT)
		return ("DIRECT");
	else if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	else if (type == INDIRECT)
		return ("INDIRECT");
	else if (type == SEPARATOR)
		return ("SEPARATOR");
	else if (type == COMMENT)
		return ("COMMENT");
	return ("END");
}

static void	print_token(t_token token)
{
	ft_printf("Token type %s ; Token size %zu ; Token string \"%s\"\n",
		string_for_type(token.type), token.size, token.string);
}

/*
** TODO: keep tokens to be processed later
** TODO: handle errors (LEX AND MEM)
** TODO: calc position with i
*/

void		asm_parse(t_asm *asm_t)
{
	size_t	i;
	t_token	current;

	gnl_to_one_string(asm_t);
	i = 0;
	while (i <= (size_t)asm_t->file_size)
	{
		current = get_next_token(asm_t->file, i);
		i += current.size;
		i += first_non_space(asm_t->file + i) - (asm_t->file + i);
		if (asm_t->file[i] == '#')
			while (asm_t->file[i] && asm_t->file[i] != '\n')
				i++;
		print_token(current);
		free(current.string);
	}
}
