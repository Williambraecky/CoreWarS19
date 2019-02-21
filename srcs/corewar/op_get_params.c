/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_get_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:33:10 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/21 14:49:04 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_type_code(t_vm *vm, t_process *process, int i)
{
	int		ret;
	int		code;

	ret = 1;
	code = vm->arena.arena[(process->pc + 1) % MEM_SIZE] >> (6 - 2 * i) & 0x03;
	code = (code == 3 ? 4: code);
	if (!(code & process->instruction.types[i]))
		return (0);
	process->instruction.types[i] = (char)code;
	return (1);
}

static int	check_code_octet(t_vm *vm, t_process *process)
{
	int		i;

	i = 0;
	while (i < process->instruction.nb_arg)
	{
		if (!check_type_code(vm, process, i))
		{
			process->instruction.types[0] = -1;
			return (0);
		}
		i++;
	}
	while (i < 4)
	{
		if (vm->arena.arena[(process->pc + 1) % MEM_SIZE] >> (6 - 2 * i) & 0x03)
		{
			process->instruction.types[0] = -1;
			return (0);
		}
		i++;
	}
	//printf("ret 0\n");
	return (1);
}

static int	sizearg(t_arg_type arg, int dir_size)
{
	if (arg != 2)
		return ((arg % 2) ? arg: arg / 2);
	return (dir_size);
}

/*
 * J'ai pas encore mis en static, peut etre on aura besoin autre part,
 * inch'allah. ET CA S EST PRODUIT, hourrah.
 */

int			big_end_toi(unsigned char *arena, int pc, int size)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (i < size)
	{
		ret = ret * 256 + arena[(pc + i) % MEM_SIZE]; 
		i++;
	}
	//pour que ca devienne negatif s'il le faut
	if (size == 2)
		ret = (int)(short)(ret);
	return (ret);
}

/*
 * le adv il sera a 1 s'il y a un probleme (octet d'encodage ou index registre)
 * ou le nombre a avancer si pas de soucis
 */

void		op_get_params(t_vm *vm, t_process *process)
{
	int			i;
	int			j;
	int			adv;
	t_instruct	inst;

	inst = process->instruction;
	if (inst.code_octet && !check_code_octet(vm, process))
		return ;
	adv = 1 + inst.code_octet;
	i = 0;
	while (i < 3)
	{
		j = sizearg(process->instruction.types[i], inst.label_size ? 2: 4);
		process->instruction.value[i] = big_end_toi(vm->arena.arena, process->pc + adv, j);
		adv += j;
		if (process->instruction.types[i] == T_REG &&
				(process->instruction.value[i] < 1 ||
				process->instruction.value[i] > REG_NUMBER))
		{
			process->instruction.types[0] = -1;
			return ;
		}
		i++;
	}
	process->instruction.adv = adv;
}
