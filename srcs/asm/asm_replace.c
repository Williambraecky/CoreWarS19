/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:33:44 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 18:28:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	handle_error(t_asm *asm_t, t_token token)
{
	ft_printf_fd(2, "No such label %s while attempting to dereference \
token [TOKEN][%.3d:%.3d] %s \"%s\"\n",
		token.string + 2, token.pos.y, token.pos.x, type_get_string(token.type),
		token.string);
	free_asm(asm_t);
	exit(0);
}

static void	handle_replace(t_asm *asm_t, t_label replace, t_label *found)
{
	int		s;
	size_t	i;
	size_t	j;
	t_u8	*octets;

	s = found->position - replace.position;
	if (replace.label_size)
		i = 2;
	else
		i = 4;
	octets = (t_u8*)&s;
	j = 0;
	while (i--)
		asm_t->code[replace.code_pos + j++] = octets[i];
}

void		asm_replace_labels(t_asm *asm_t)
{
	size_t	i;
	t_label	replace;
	t_label	*found;

	i = 0;
	while (i < asm_t->nb_replace)
	{
		replace = asm_t->replace[i];
		found = get_label(asm_t, replace.name);
		if (!found)
			handle_error(asm_t, replace.token);
		handle_replace(asm_t, replace, found);
		i++;
	}
}
