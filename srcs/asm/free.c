/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:09:17 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 11:28:45 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Free future stuff
*/

void	free_asm(t_asm *asm_t)
{
	if (asm_t->replace)
		ft_memdel((void**)&asm_t->replace);
	if (asm_t->labels)
		ft_memdel((void**)&asm_t->labels);
	if (asm_t->file)
		ft_strdel(&asm_t->file);
}
