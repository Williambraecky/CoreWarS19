/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:05:59 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/28 14:56:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*g_trophy[41] =
{
	"            `...-::::---------.---....`.",
	"         ./hso+/-..``        `-:/++-` ./s+:",
	"         :+:ooso/+/:::......-:/+sso/+o:/oms",
	" ..      /.-...-...-:-.-::////:/:/:+hh+shmN      `-",
	"`o.:..-. .++:.:+/:::::::--:::-:::/+shysshd.`.-::/s/`",
	"-y/--------+-``+:.---++::-::--:.-.-:/:.-so/o+/:--/s",
	":y`:` .::-:o:``/``..`/:`.``...-```:o+-./ho/:/.  -:y-",
	"-m-:  //`/d+/ `:   ``:-` `````.`../o+-.+h+`./s  .:y.",
	" y/.:  -//-.s-`:     :`   `   . ../+/--ss-://. `-y+",
	" `o/.:      +: /     :`   `   .`-./o:-:y:     .:o:",
	"  `s/-:`    .s : `   :`   `   .`-.//::+y     -:+.",
	"    :s::-    +`:. `  -`   `   ....:o:/y-   .+/-",
	"     `:o/:.  -/`/ `  .`   ` ``..../o/+o   :o+.",
	"       `+:::  o`-:`  `-   ``` .`..//:y- .o++.",
	"        `//-:../ :-.  .    ```....+/+o`+h/.",
	"          ./+::/``:..`..      ...:o/d+ho.",
	"            `+o/o .-.`.:``   `--:sosys-",
	"              `+o/`.-.`:.  ``..-++ys/",
	"               `s+s:....+` `..-ooys/",
	"               :/y+-+/-.-o//+oyy+./+:",
	"                     -+ssooohy+`",
	"                    :--::///++oo`",
	"                    `:+:-:://oys",
	"                      +/::+y//:",
	"                     `::.`+s-o-",
	"                  `----+ `yh::/o/-`",
	"             `://:-.-/:  .sso:-/ssd+//",
	"             /+/o./++.` .:soso+/ydmd+o/",
	"            .///o+so-.--++osssyy+odsoyy`",
	"            ::--:-oy:..-++ossydho/-:osos",
	"           .--::+-.----:+oysoo+:--:osyyh+",
	"           :`..------..-------::/::-.---+",
	"           o``..--.....```  ```` ``/----o:",
	"          ::``..-`                 /....oo",
	"         `+--```..                `/-.--sy.",
	"         /::-```.:..---------:---.--::/:so+",
	"        .o:+:.---------.----:--::-:::///oo+/",
	"        o+-........-...--:---------------:os.",
	"       -o-..--.--:-------....-----:::://++:os",
	"       o:............---------......--::::::o:",
	"      `:...-------------..------------:::::::-",
};

void		print_winner(t_vm *vm, WINDOW *window)
{
	t_champ	winner;

	winner = vm->champs[vm->arena.winner];
	if (vm->arena.winner -= -1)
	{
		wattron(window, COLOR_PAIR(6));
		print_on_window(window, g_trophy, 41);
		wmove(window, 44, 19);
		wprintw(window, "PLAYER %d WON!!", winner.number);
		wattroff(window, COLOR_PAIR(6));
		wattron(window, COLOR_PAIR(vm->arena.winner));
		wmove(window, 46, 26 -
			ft_min(26, ft_strlen(winner.code.header.prog_name) / 2));
		wprintw(window, "%s", winner.code.header.prog_name);
		wattroff(window, COLOR_PAIR(vm->arena.winner));
	}
	else
		wprintw(window, "%s", "NO WINNER AS NO CONTESTANT DID A LIVE.");
	wrefresh(window);
}
