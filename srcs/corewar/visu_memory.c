/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:19:41 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/21 18:14:35 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			setup_color(t_vm *vm, int i)
{
	int	j;

	j = -1;
	if (ft_abs(vm->arena.arena_owner[i] < 5))
			return (ft_abs(vm->arena.arena_owner[i]));
	return (5);
}

void		print_memory(t_vm *vm, WINDOW *window)
{
	int	i;
	int	color;
	int sign;

	werase(window);
	wmove(window, 1, 1);
	i = -1;
	while (++i < MEM_SIZE)
	{
		sign = (vm->arena.arena_owner[i] < 0 ? 1 : 0);
		color = setup_color(vm, i);
		wattron(window, COLOR_PAIR(color));
		sign ? wattron(window, A_REVERSE): 0;
		wprintw(window, "%02x", ft_abs(vm->arena.arena[i]));
		sign ? wattroff(window, A_REVERSE): 0;
		wattroff(window, COLOR_PAIR(color));
		if ((i + 1) % 64 == 0)
			wprintw(window, "\n ");
		else
			wprintw(window, " ");
	}
	wrefresh(window);
}

void		print_player(t_vm *vm, WINDOW *window, int index)
{
	int		decal;
	t_champ	champ;
	int		y_ref;

	y_ref = 8;
	champ = vm->champs[index];
	decal = index * 5;
	wmove(window, y_ref++ + decal, 2);
	wprintw(window, "Player - %d: ", champ.number);
	wattron(window, COLOR_PAIR(index + 1));
	wprintw(window,"%s", champ.code.header.prog_name);
//	wprintw(window,"%d\n", champ.code.header.prog_size);
	wattroff(window, COLOR_PAIR(index + 1));
	wmove(window, y_ref++ + decal, 6);
	wprintw(window, "Last live: \t\t\t\t%d", champ.lives);
	wmove(window, y_ref + decal, 6);
	wprintw(window, "Lives in current period: \t\t\t%d", champ.lives_since_last_check);
}

void		print_players(t_vm *vm, WINDOW *window)
{
	int	i;

	i = -1;
	while (++i < vm->nbr_champ)
		print_player(vm, window, i);
}

void		print_data(t_vm *vm, WINDOW *window)
{
	int		decal;

	decal = vm->nbr_champ * 7;
	werase(window);
	wmove(window, 3, 30);
	vm->visu_pause ? 
		wprintw(window, "%s", "~*'*~ PAUSE! ~*'*~"):
		wprintw(window, "%s", "~*'*~ FIGHT! ~*'*~");
	wmove(window, 5, 2);
	wprintw(window, "Cycle : %d", vm->arena.total_cycle);
	wmove(window, 6, 2);
	wprintw(window, "Process : %d", vm->arena.nbr_process_alive);
	print_players(vm, window);
	wmove(window, 5 + decal, 10);
	wprintw(window, "_________________________________________________");
	wmove(window, 8 + decal, 2);
	wprintw(window, "Cycles to die: %d", vm->arena.cycle_to_die);
	wmove(window, 10 + decal, 2);
	wprintw(window, "Cycle delta: %d", CYCLE_DELTA);
	wmove(window, 12 + decal, 2);
	wprintw(window, "Speed: %d", vm->visu_speed);
	wmove(window, 61, 2);
	wprintw(window, "COMMANDS :\n\tSPACE \t: Pause/Start\n");
	wprintw(window, "\tESC \t: Quit\n\t+ \t: Speed up\n\t- \t: Speed down");
	wrefresh(window);
}
