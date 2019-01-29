/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:44:28 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/29 16:30:24 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		init_vm(t_vm *vm)
{
	vm->dump = -1;
	vm->nbr_champ = 0;
	vm->n = 0;
	vm->arena.cycle_to_die = CYCLE_TO_DIE;
	vm->arena.cycle_left = CYCLE_TO_DIE;
	vm->arena.nbr_process = 0;
	vm->arena.nbr_process_alive = 0;
}
