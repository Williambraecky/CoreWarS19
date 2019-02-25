/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:05:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/25 10:56:31 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		set_line1(char **line)
{
	line[0] = "            `...-::::---------.---....`.";
	line[1] = "         ./hso+/-..``        `-:/++-` ./s+:";
	line[2] = "         :+:ooso/+/:::......-:/+sso/+o:/oms";
	line[3] = " ..      /.-...-...-:-.-::////:/:/:+hh+shmN      `-";
	line[4] = "`o.:..-. .++:.:+/:::::::--:::-:::/+shysshd.`.-::/s/`";
	line[5] = "-y/--------+-``+:.---++::-::--:.-.-:/:.-so/o+/:--/s";
	line[6] = ":y`:` .::-:o:``/``..`/:`.``...-```:o+-./ho/:/.  -:y-";
	line[7] = "-m-:  //`/d+/ `:   ``:-` `````.`../o+-.+h+`./s  .:y.";
	line[8] = " y/.:  -//-.s-`:     :`   `   . ../+/--ss-://. `-y+";
	line[9] = " `o/.:      +: /     :`   `   .`-./o:-:y:     .:o:";
	line[10] = "  `s/-:`    .s : `   :`   `   .`-.//::+y     -:+.";
	line[11] = "    :s::-    +`:. `  -`   `   ....:o:/y-   .+/-";
	line[12] = "     `:o/:.  -/`/ `  .`   ` ``..../o/+o   :o+.";
	line[13] = "       `+:::  o`-:`  `-   ``` .`..//:y- .o++.";
	line[14] = "        `//-:../ :-.  .    ```....+/+o`+h/.";
	line[15] = "          ./+::/``:..`..      ...:o/d+ho.";
	line[16] = "            `+o/o .-.`.:``   `--:sosys-";
	line[17] = "              `+o/`.-.`:.  ``..-++ys/";
	line[18] = "               `s+s:....+` `..-ooys/";
	line[19] = "               :/y+-+/-.-o//+oyy+./+:";
	line[20] = "                     -+ssooohy+`";
	line[21] = "                    :--::///++oo`";
	line[22] = "                    `:+:-:://oys";
}

void		set_line2(char **line)
{
	line[23] = "                      +/::+y//:";
	line[24] = "                     `::.`+s-o-";
	line[25] = "                  `----+ `yh::/o/-`";
	line[26] = "             `://:-.-/:  .sso:-/ssd+//";
	line[27] = "             /+/o./++.` .:soso+/ydmd+o/";
	line[28] = "            .///o+so-.--++osssyy+odsoyy`";
	line[29] = "            ::--:-oy:..-++ossydho/-:osos";
	line[30] = "           .--::+-.----:+oysoo+:--:osyyh+";
	line[31] = "           :`..------..-------::/::-.---+";
	line[32] = "           o``..--.....```  ```` ``/----o:";
	line[33] = "          ::``..-`                 /....oo";
	line[34] = "         `+--```..                `/-.--sy.";
	line[35] = "         /::-```.:..---------:---.--::/:so+";
	line[36] = "        .o:+:.---------.----:--::-:::///oo+/";
	line[37] = "        o+-........-...--:---------------:os.";
	line[38] = "       -o-..--.--:-------....-----:::://++:os";
	line[39] = "       o:............---------......--::::::o:";
	line[40] = "      `:...-------------..------------:::::::-";
}

void		print_winner(t_vm *vm, WINDOW *window)
{
	char	*line[41];
	t_champ	winner;

	winner = vm->champs[vm->arena.winner];
	if (vm->arena.winner -= -1)
	{
		set_line1(line);
		set_line2(line);
		wattron(window, COLOR_PAIR(6));
		print_on_window(window, line, 41);
		wmove(window, 44, 19);
		wprintw(window, "PLAYER %d WON!!", winner.number);
		wattroff(window, COLOR_PAIR(6));
		wattron(window, COLOR_PAIR(vm->arena.winner));
		wmove(window, 46, 16);
		wprintw(window, "%s", winner.code.header.prog_name);
		wattroff(window, COLOR_PAIR(vm->arena.winner));
	}
	else
		wprintw(window, "%s", "NO WINNER AS NO CONTESTANT DID A LIVE.");
	wrefresh(window);
}
