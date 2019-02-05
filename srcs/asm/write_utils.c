/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:54:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/03 15:56:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ensure_enough_space(t_asm *asm_t)
{
	t_u8	*new;
	size_t	new_size;

	if (asm_t->champ.header.prog_size < asm_t->current_code_max)
		return ;
	if (CODE_MAX_START == 0)
		exit_error(asm_t, "CODE MAX START cannot be 0");
	if (asm_t->current_code_max == 0)
		new_size = CODE_MAX_START;
	else
		new_size = asm_t->current_code_max * 2;
	if (!(new = ft_realloc(asm_t->code, asm_t->current_code_max, new_size)))
		exit_error(asm_t, "Out of memory");
	asm_t->current_code_max = new_size;
	asm_t->code = new;
}

void		code_write_byte(t_asm *asm_t, t_u8 byte)
{
	ensure_enough_space(asm_t);
	if (!asm_t->code)
		exit_error(asm_t, "Could not ensure enough space for code\n");
	asm_t->code[asm_t->champ.header.prog_size++] = byte;
}

/*
** Writes multiple bytes, warning /!\ writes them in reverse
*/

void		code_write_bytes(t_asm *asm_t, t_u8 *bytes, size_t size)
{
	while (size--)
		code_write_byte(asm_t, bytes[size]);
}
