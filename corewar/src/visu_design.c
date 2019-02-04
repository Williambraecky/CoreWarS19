/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_design.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:05:26 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/04 15:14:55 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		print_header(t_vm *vm, WINDOW *window)
{
	werase(window);
	wmove(window, 2, 75);
	wprintw(window, "%s", "GET READY FOR THE BATTLE OF THE YEAR");
	wmove(window, 4, 71);
	wprintw(window, "%s", " _____ ___________ _____ _    _  ___ ______\n");
	wmove(window, 5, 71);
	wprintw(window, "%s", "/  __ \\  _  | ___ \\  ___| |  | |/ _ \\| ___ \\\n");
	wmove(window, 6, 71);
	wprintw(window, "%s", "| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\ |_/ /\n");
	wmove(window, 7, 71);
	wprintw(window, "%s", "| |   | | | |    /|  __|| |/\\| |  _  |    /\n");
	wmove(window, 8, 71);
	wprintw(window, "%s", "| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | | |\\ \\\n");
	wmove(window, 9, 71);
	wprintw(window, "%s", " \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_|_| \\_|\n");
	wrefresh(window);
}

void		print_on_window(WINDOW *window, char **line, int size)
{
	int	i;
	int	x;
	int	y;

	getyx(window, y, x);
	i = -1;
	y++;
	x++;
	while (++i < size)
	{
		wmove(window, y + i, x);
		wprintw(window, "%s", line[i]);
	}
}

void		print_19ai(WINDOW *window)
{
	char	*line[12];

	line[0] = "     -hNNNNNN-  ommmmmmmmmh/              -h: -dNNNNh.";
	line[1] = "  `:hMMMMMMMM:  sMMMMMMMMMMMd+`          /mNNo``yNNNNm:";
	line[2] = " :hNNNNMMMMMM:  /mMMMNsooomMMMm-       `oNNNNNh. +NNNNNo`";
	line[3] = "`.....:MMMMMM:   `+mMMNs. yMMMM/      .yNNNNNNNm: -dNNNNy.";
	line[4] = "      .MMMMMM:     `/hddh/hMMMM/     -dNNNd:sNNNNo``sNNNNm:";
	line[5] = "      .MMMMMM:            yMMMM/    /mNNNs`  +mNNNy. /mNNNNo`";
	line[6] = "      .MMMMMM:   `````````hMMMM/  `sNNNm+     -dNNNm: -hNNNNy.";
	line[7] = "      .MMMMMM:  `+dmmmmmmmNMMMM/ .hNNNd-       `sNNNNo``sNNNNd:";
	line[8] = "      .MMMMMM:    .oNMMMMMMMMMM/-dNNNy.          /mNNNh. /mNNNNo";
	line[9] = "      .MMMMMM:      ./+++++++++sNNNNo`            -dNNNm: .hNNNNy.";
	line[10] = "      .MMMMMM:               `sNNNNh+++++++++/     `sNNNNo `oNNNNm: ";
	line[11] = "      .MMMMMM:              `hNNNNNNNNNNNNNNNNy`     /mNNNy` :mNNNN+";
	print_on_window(window, line, 12);
	wrefresh(window);
}
