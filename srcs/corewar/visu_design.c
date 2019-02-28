/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_design.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:05:26 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 14:10:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*g_ai_logo[12] =
{
	"      -hNNNNNN-  ommmmmmmmmh/              -h: -dNNNNh.",
	"   `:hMMMMMMMM:  sMMMMMMMMMMMd+`          /mNNo``yNNNNm:",
	"  :hNNNNMMMMMM:  /mMMMNsooomMMMm-       `oNNNNNh. +NNNNNo`",
	" `.....:MMMMMM:   `+mMMNs. yMMMM/      .yNNNNNNNm: -dNNNNy.",
	"\t.MMMMMM:     `/hddh/hMMMM/     -dNNNd:sNNNNo``sNNNNm:",
	"\t.MMMMMM:            yMMMM/    /mNNNs`  +mNNNy. /mNNNNo`",
	"\t.MMMMMM:   `````````hMMMM/  `sNNNm+     -dNNNm: -hNNNNy.",
	"\t.MMMMMM:  `+dmmmmmmmNMMMM/ .hNNNd-       `sNNNNo``sNNNNd:",
	"\t.MMMMMM:    .oNMMMMMMMMMM/-dNNNy.\t   /mNNNh. /mNNNNo",
	"\t.MMMMMM:      ./+++++++++sNNNNo`\t    -dNNNm: .hNNNNy.",
	"\t.MMMMMM:\t\t`sNNNNh+++++++++/     `sNNNNo `oNNNNm: ",
	"\t.MMMMMM:\t       `hNNNNNNNNNNNNNNNNy`     /mNNNy` :mNNNN+",
};

char		*g_header[7] =
{
	"GET READY FOR THE BATTLE OF THE YEAR",
	" _____ ___________ _____ _    _  ___ ______\n",
	"/  __ \\  _  | ___ \\  ___| |  | |/ _ \\| ___ \\\n",
	"| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\ |_/ /\n",
	"| |   | | | |    /|  __|| |/\\| |  _  |    /\n",
	"| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | | |\\ \\\n",
	" \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_|_| \\_|\n",
};

void		print_header(WINDOW *w)
{
	werase(w);
	wmove(w, 2, 75);
	wprintw(w, "%s", g_header[0]);
	wmove(w, 4, 71);
	wprintw(w, "%s", g_header[1]);
	wmove(w, 5, 71);
	wprintw(w, "%s", g_header[2]);
	wmove(w, 6, 71);
	wprintw(w, "%s", g_header[3]);
	wmove(w, 7, 71);
	wprintw(w, "%s", g_header[4]);
	wmove(w, 8, 71);
	wprintw(w, "%s", g_header[5]);
	wmove(w, 9, 71);
	wprintw(w, "%s", g_header[6]);
	wrefresh(w);
}

void		print_on_window(WINDOW *window, char **line, int size)
{
	int	i;
	int	x;
	int	y;

	getyx(window, y, x);
	i = 0;
	y++;
	x++;
	while (i < size)
	{
		wmove(window, y + i, x);
		wprintw(window, "%s", line[i]);
		i++;
	}
}

void		print_19ai(WINDOW *window)
{
	print_on_window(window, g_ai_logo, 12);
	wrefresh(window);
}
