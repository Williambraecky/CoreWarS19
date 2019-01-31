/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:44:28 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/31 18:12:33 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		init_vm(t_vm *vm)
{
	vm->dump = -1;
	vm->nbr_champ = 0;
	vm->n = 0;
	vm->arena.cycle_to_die = CYCLE_TO_DIE;
	vm->arena.cycle_since_check = 0;
	vm->arena.nbr_process = 0;
	vm->arena.nbr_process_alive = 0;
	vm->arena.winner = -1;
	vm->dump = -1;
	vm->arena.total_cycle = 0;
	vm->arena.lives_since_last_check = 0;
}
