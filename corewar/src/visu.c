/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:28:19 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/01 21:53:42 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		init_visu(WINDOW **window)
{
	initscr();
	start_color();
	window[0] = newwin(14, 74, 0, 201); //19
	window[1] = newwin(80, 200, 11, 0); //memory
	window[2] = newwin(200, 80, 15, 201); // data
	window[3] = newwin(200, 80, 15, 201); //winner
	window[4] = newwin(10, 200, 0, 0); //header
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_color(COLOR_CYAN, 400, 400, 400);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	box(window[0], 0, 0);
	box(window[1], 0, 0);
	box(window[2], 0, 0);
	box(window[3], 0, 0);
	box(window[4], 0, 0);
}

void		print_visu(t_vm *vm, WINDOW **window, int mode)
{
	curs_set(0);
	clear();
	if (mode)
	{
		print_19ai(window[0]);
		print_memory(vm, window[1]);
		print_data(vm, window[2]);
		print_header(vm, window[4]);
		usleep(50000);
	}
	else
	{
		print_19(window[0]);
		print_data(vm, window[2]);
		print_winner(vm, window[3]);
		print_header(vm, window[4]);
	}
}
