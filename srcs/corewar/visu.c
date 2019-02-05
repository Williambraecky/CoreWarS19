/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:28:19 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/05 17:24:37 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_visu(WINDOW **window)
{
	initscr();
	start_color();
	window[0] = newwin(14, 74, 1, 198); //19
	window[1] = newwin(66, 195, 16, 3); //memory
	window[2] = newwin(66, 74, 15, 197); // data
	window[5] = newwin(66, 74, 15, 197); // data
	window[3] = newwin(63, 65, 18, 207); //winner
	window[4] = newwin(12, 197, 1, 1); //header
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_color(COLOR_CYAN, 400, 400, 400);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_color(COLOR_MAGENTA, 999, 999, 0);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	box(window[0], 0, 0);
	box(stdscr, 0, 0);
	keypad(stdscr, TRUE);
}

void		press_key(t_vm *vm, char mode)
{
	int		key;

	key = 0;
	if (mode)
		nodelay(stdscr, 1);
	key = getch();
	noecho();
	if (mode)
		nodelay(stdscr, 0);
	if (key == '-' && vm->visu_speed > 0)
		vm->visu_speed -= 10;
	if (key == '+' && vm->visu_speed < 500)
		vm->visu_speed += 10;
	if (key == 32)
		vm->visu_pause = !vm->visu_pause;
	if (key == 27)
		error_exit(vm, "You left the battlefield!");
}

void		print_data2(WINDOW *window)
{
	werase(window);
	wrefresh(window);
}


void		print_visu(t_vm *vm, WINDOW **window, int mode)
{
	curs_set(0);
	press_key(vm, 1);
	if (mode)
	{
		print_19ai(window[0]);
		print_memory(vm, window[1]);
		print_data(vm, window[2]);
		print_header(window[4]);
		usleep(50000 - (vm->visu_speed * 100));
	}
	else
	{
		werase(window[2]);
		print_data2(window[5]);
		print_19ai(window[0]);
		print_memory(vm, window[1]);
		print_winner(vm, window[3]);
		print_header(window[4]);
		press_key(vm, 0);
	}
}
