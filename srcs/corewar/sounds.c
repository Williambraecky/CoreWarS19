/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:16:34 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/22 18:49:32 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			play_victory(t_vm *vm)
{
	if (vm->sounds)
	{
		system("pkill afplay");
		system("afplay srcs/sounds/victory.wav &> /dev/null &");
	}
	return (1);
}

int			play_death(t_vm *vm)
{
	if (vm->sounds && vm->sounds_death == 1)
	{
		system("pkill afplay");
		system("afplay srcs/sounds/death.wav &> /dev/null &");
	}
	return (1);
}

int			play_born(t_vm *vm)
{
	if (vm->sounds && vm->sounds_born == 1)
	{
		system("pkill afplay");
		system("afplay srcs/sounds/born.wav &> /dev/null &");
	}
	return (1);
}
