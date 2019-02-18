/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlabel_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:48:20 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/05 15:06:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		dlabel_of_type(char *line, size_t i)
{
	if (line[i] != DIRECT_CHAR || line[i + 1] != LABEL_CHAR)
		return (0);
	return (ft_strchr(LABEL_CHARS, line[i + 2]) != NULL);
}

t_token	dlabel_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = DIRECT_LABEL;
	j = i + 2;
	while (line[j])
	{
		if (ft_strchr(SEPARATOR_CHARS, line[j])
		|| !ft_strchr(LABEL_CHARS, line[j]))
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

void	process_dlabel(t_asm *asm_t, t_token token, int label_size,
	int instruction_pos)
{
	t_label	*label;
	int		s;

	label = get_label(asm_t, token.string + 2);
	if (label == NULL)
	{
		s = 0;
		asm_add_replace(asm_t,
			(t_repl){.name = ft_strjoin(token.string + 2, ":"),
			.position = instruction_pos, .token = token,
			.label_size = label_size,
			.code_pos = asm_t->champ.header.prog_size});
	}
	else
		s = (int)(label->position - instruction_pos);
	code_write_bytes(asm_t, (t_u8*)&s, label_size ? 2 : 4);
}
