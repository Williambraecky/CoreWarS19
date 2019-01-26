/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:08:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/26 15:57:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** handle this type of error
** Invalid parameter 0 type register for instruction live
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

void	syntax_error(t_asm *asm_t, int column, char *type, char *addition)
{
	if (addition)
		ft_printf_fd(2, "Syntax error at token [TOKEN][%.3d:%.3d] %s \"%s\"\n",
			asm_t->line, column, type, addition);
	else
		ft_printf_fd(2, "Syntax error at token [TOKEN][%.3d:%.3d] %s\n",
			asm_t->line, column, type);
	free_asm(asm_t);
	exit(0);
}

void	lexical_error(t_asm *asm_t, int column)
{
	ft_printf_fd(2, "Lexical error at [%d:%d]\n", asm_t->line, column);
	free_asm(asm_t);
	exit(0);
}

/*
** Print usage then exit
*/

void	exit_usage(char *prog_name)
{
	ft_printf_fd(2, "Usage: %s <sourcefile.s>\n", prog_name);
	exit(0);
}
