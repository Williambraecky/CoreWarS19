/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:42:30 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/19 07:18:32 by cvan-bee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static const t_instruct		g_op_list[17] = {
	{0, op_null, 1, 0, {}, {0, 0, 0}, 0, 0, 1},
	{1, op_live, 10, 1, {T_DIR}, {0, 0, 0}, 0, 0, 1},
	{2, op_ld, 5, 2, {T_DIR | T_IND, T_REG}, {0, 0, 0}, 1, 0, 1},
	{3, op_st, 5, 2, {T_REG, T_IND | T_REG}, {0, 0, 0}, 1, 0, 1},
	{4, op_add, 10, 3, {T_REG, T_REG, T_REG}, {0, 0, 0}, 1, 0, 1},
	{5, op_sub, 10, 3, {T_REG, T_REG, T_REG}, {0, 0, 0}, 1, 0, 1},
	{6, op_and, 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},\
		{0, 0, 0}, 1, 0, 1},
	{7, op_or, 6, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		{0, 0, 0}, 1, 0, 1},
	{8, op_xor, 6, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		{0, 0, 0}, 1, 0, 1},
	{9, op_zjmp, 20, 1, {T_DIR}, {0, 0, 0}, 0, 1, 1},
	{10, op_ldi, 25, 3, {T_REG | T_IND | T_DIR, T_DIR | T_REG, T_REG},\
		{0, 0, 0}, 1, 1, 1},
	{11, op_sti, 25, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},\
		{0, 0, 0}, 1, 1, 1},
	{12, op_fork, 800, 1, {T_DIR}, {0, 0, 0}, 0, 1, 1},
	{13, op_lld, 10, 2, {T_DIR | T_IND, T_REG}, {0, 0, 0}, 1, 0, 1},
	{14, op_lldi, 50, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		{0, 0, 0}, 1, 1, 1},
	{15, op_lfork, 1000, 1, {T_DIR}, {0, 0, 0}, 0, 1, 1},
	{16, op_aff, 2, 1, {T_REG}, {0, 0, 0}, 1, 0, 1}
};

t_instruct	read_instruction(t_vm *vm, int pc)
{
	if (vm->arena.arena[pc] != 0 && vm->arena.total_cycle < 50)
		printf("instruct read : %d\n", vm->arena.arena[pc]);
	if (vm->arena.arena[pc] > 16)
		return (g_op_list[0]);
	else
		return (g_op_list[vm->arena.arena[pc]]);
}
