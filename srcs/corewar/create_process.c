/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:13:08 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/01 11:09:34 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			set_process(t_vm *vm, t_process *process)
{
	int			i;

	i = -1;
	vm->arena.nbr_process++;
	vm->arena.nbr_process_alive++;
	process->index_arena = 0;
	process->index_champ = 0;
	process->alive = 1;
	while (++i < REG_NUMBER)
		process->registre[i] = 0;
	process->pc = 0;
	process->carry = 0;
	process->lives_since_check = 0;
	process->number = vm->arena.nbr_process;
}
