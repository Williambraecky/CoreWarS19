/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilabel_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:03:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/05 15:07:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ilabel_of_type(char *line, size_t i)
{
	if (line[i] != LABEL_CHAR || !ft_strchr(LABEL_CHARS, line[i + 1]))
		return (0);
	return (1);
}

t_token	ilabel_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = INDIRECT_LABEL;
	j = i + 1;
	while (line[j])
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

void	process_ilabel(t_asm *asm_t, t_token token, int instruction_pos)
{
	t_label *label;
	int		s;

	label = get_label(asm_t, token.string + 1);
	if (label == NULL)
	{
		s = 0;
		asm_add_replace(asm_t,
			(t_repl){.name = ft_strjoin(token.string + 1, ":"),
			.position = instruction_pos, .token = token,
			.label_size = 1,
			.code_pos = asm_t->champ.header.prog_size});
	}
	else
		s = (int)(label->position - instruction_pos);
	code_write_bytes(asm_t, (t_u8*)&s, 2);
}
