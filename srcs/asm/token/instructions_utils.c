/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:49:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/05 15:02:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_u8	get_type_for(t_type type)
{
	if (type == REGISTER)
		return (T_REG);
	else if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == LABEL)
		return (T_LAB);
	return (0);
}

int			instruction_check_param(t_op *op, t_token param, int param_count)
{
	t_u8	type;

	if (param_count >= op->nb_arg)
		return (0);
	if (!(type = get_type_for(param.type)))
		return (0);
	return (op->types[param_count] & type);
}

void		process_parameter(t_asm *asm_t, t_token parameter, int label_size,
	int instruction_pos)
{
	if (parameter.type == DIRECT)
		process_direct(asm_t, parameter, label_size);
	else if (parameter.type == INDIRECT)
		process_indirect(asm_t, parameter);
	else if (parameter.type == INDIRECT_LABEL)
		process_ilabel(asm_t, parameter, instruction_pos);
	else if (parameter.type == DIRECT_LABEL)
		process_dlabel(asm_t, parameter, label_size, instruction_pos);
	else if (parameter.type == REGISTER)
		process_register(asm_t, parameter);
}

char		*get_error_string_for_type(t_type type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return ("direct");
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return ("indirect");
	else if (type == REGISTER)
		return ("register");
	return ("");
}
