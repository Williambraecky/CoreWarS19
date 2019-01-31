/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:09:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 15:23:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_tokens(t_asm *asm_t)
{
	size_t	i;

	i = 0;
	while (i < asm_t->nb_tokens)
		ft_strdel((char**)&(asm_t->tokens[i++].string));
	ft_memdel((void**)&asm_t->tokens);
}

static void	free_labels(t_asm *asm_t)
{
	size_t	i;

	if (asm_t->labels)
	{
		i = 0;
		while (i < asm_t->nb_labels)
			ft_strdel((char**)&(asm_t->labels[i++].name));
		ft_memdel((void**)asm_t->labels);
	}
	if (asm_t->replace)
	{
		i = 0;
		while (i < asm_t->nb_replace)
			ft_strdel((char**)&(asm_t->replace[i++].name));
		ft_memdel((void**)asm_t->replace);
	}
}

/*
** Free future stuff
*/

void		free_asm(t_asm *asm_t)
{
	free_labels(asm_t);
	if (asm_t->file)
		ft_strdel(&asm_t->file);
	if (asm_t->tokens)
		free_tokens(asm_t);
	if (asm_t->code)
		ft_memdel((void**)&asm_t->code);
}
