/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:14:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 15:25:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		label_of_type(char *line, size_t i)
{
	while (line[i] && line[i] != LABEL_CHAR)
		if (!ft_strchr(LABEL_CHARS, line[i++]))
			return (0);
	return (line[i] == LABEL_CHAR);
}

t_token	label_make_token(char *line, size_t i)
{
	t_token	ret;
	size_t	j;

	ret.type = LABEL;
	j = i;
	while (line[j] != LABEL_CHAR)
		j++;
	ret.string = ft_strndup(line + i, j - i + 1);
	if (!ret.string)
		ret.type = MEM_ERROR;
	else
		ret.size = ft_strlen(ret.string);
	return (ret);
}

void	process_label(t_asm *asm_t, t_token token, size_t *i)
{
	t_label	*label;

	label = get_label(asm_t, token.string);
	if (!label)
		asm_add_label(asm_t, token.string, asm_t->champ.header.prog_size);
	(*i)++;
}
