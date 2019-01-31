/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:08:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 16:38:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** handle this type of error
** TODO: Invalid parameter 0 type register for instruction live
*/

/*
** Generic error handler
*/

void	exit_error(t_asm *asm_t, char *error)
{
	if (error)
		ft_printf_fd(2, "An error occured: %s\n", error);
	else
		ft_printf_fd(2, "An unknown error occured\n");
	free_asm(asm_t);
	exit(0);
}

void	syntax_error(t_asm *asm_t, t_token token)
{
	ft_printf_fd(2, "Syntax error at token [TOKEN][%.3d:%.3d] %s \"%s\"\n",
		token.pos.y, token.pos.x, type_get_string(token.type), token.string);
	free_asm(asm_t);
	exit(0);
}

void	invalid_instruction_error(t_asm *asm_t, t_token token)
{
	ft_printf_fd(2, "Invalid instruction at token [TOKEN][%.3d:%.3d] \
	%s \"%s\"\n",
		token.pos.y, token.pos.x, type_get_string(token.type), token.string);
	free_asm(asm_t);
	exit(0);
}

void	lexical_error(t_asm *asm_t, t_pos pos)
{
	ft_printf_fd(2, "Lexical error at [%d:%d]\n", pos.y, pos.x);
	free_asm(asm_t);
	exit(0);
}

void	invalid_parameter_type_error(t_asm *asm_t,
	int param_count, t_type type, char *op_name)
{
	ft_printf_fd(2, "Invalid parameter %d type %s for instruction %s\n",
		param_count, get_error_string_for_type(type), op_name);
	free_asm(asm_t);
	exit(0);
}
