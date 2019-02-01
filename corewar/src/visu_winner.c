/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:05:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/01 19:57:32 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

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

void		print_19(WINDOW *window)
{
	char	*line[13];

	line[0] = "                              ";
	line[1] = "      .-----`  --------.      ";
	line[2] = "    .yMMMMMM- `MMMMMMMMMh-    ";
	line[3] = "  .yMMMMMMMM- `MMMMMMMMMMMh-  ";
	line[4] = " .sssshMMMMM-  :dMMm+  +MMMN  ";
	line[5] = "      :MMMMM-    :dMMm++MMMN  ";
	line[6] = "      :MMMMM-      ....oMMMN  ";
	line[7] = "      :MMMMM-          +MMMN  ";
	line[8] = "      :MMMMM-  :yhhhhhhmMMMN  ";
	line[9] = "      :MMMMM-   .sMMMMMMMMMN  ";
	line[10] = "      :MMMMM-     .+ooooooo+  ";
	line[11] = "      :MMMMM-                 ";
	line[12] = "      :mmmmm-                 ";
	print_on_window(window, line, 13);
}

void		print_19ai(WINDOW *window)
{
	char	*line[12];

	line[0] = "       -hNNNNNN-  ommmmmmmmmh/              -h: -dNNNNh.              ";
	line[1] = "    `:hMMMMMMMM:  sMMMMMMMMMMMd+`          /mNNo``yNNNNm:             ";
	line[2] = "   :hNNNNMMMMMM:  /mMMMNsooomMMMm-       `oNNNNNh. +NNNNNo`           ";
	line[3] = "  `.....:MMMMMM:   `+mMMNs. yMMMM/      .yNNNNNNNm: -dNNNNy.          ";
	line[4] = "        .MMMMMM:     `/hddh/hMMMM/     -dNNNd:sNNNNo``sNNNNm:         ";
	line[5] = "        .MMMMMM:            yMMMM/    /mNNNs`  +mNNNy. /mNNNNo`       ";
	line[6] = "        .MMMMMM:   `````````hMMMM/  `sNNNm+     -dNNNm: -hNNNNy.      ";
	line[7] = "        .MMMMMM:  `+dmmmmmmmNMMMM/ .hNNNd-       `sNNNNo``sNNNNd:     ";
	line[8] = "        .MMMMMM:    .oNMMMMMMMMMM/-dNNNy.          /mNNNh. /mNNNNo    ";
	line[9] = "        .MMMMMM:      ./+++++++++sNNNNo`            -dNNNm: .hNNNNy.  ";
	line[10] = "        .MMMMMM:               `sNNNNh+++++++++/     `sNNNNo `oNNNNm: ";
	line[11] = "        .MMMMMM:              `hNNNNNNNNNNNNNNNNy`     /mNNNy` :mNNNN+";
	print_on_window(window, line, 12);
	wrefresh(window);
}

void		print_winner(t_vm *vm, WINDOW *window)
{
	werase(window);
	wrefresh(window);

}

void		print_header(t_vm *vm, WINDOW *window)
{
	werase(window);
	wmove(window, 2, 75);
	wprintw(window, "%s", "GET READY FOR THE BATTLE OF THE YEAR");
	wmove(window, 4, 71);
	wprintw(window, "%s", " _____ ___________ _____ _    _  ___ ______");
	wmove(window, 5, 71);
	wprintw(window, "%s", "/  __ \\  _  | ___ \\  ___| |  | |/ _ \\| ___ \\");
	wmove(window, 6, 71);
	wprintw(window, "%s", "| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\ |_/ /");
	wmove(window, 7, 71);
	wprintw(window, "%s", "| |   | | | |    /|  __|| |/\\| |  _  |    /");
	wmove(window, 8, 71);
	wprintw(window, "%s", "| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | | |\\ \\");
	wmove(window, 9, 71);
	wprintw(window, "%s", " \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_|_| \\_|");
	wmove(window, 11, 75);
	wrefresh(window);
}
