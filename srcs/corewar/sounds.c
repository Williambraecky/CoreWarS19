/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:16:34 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/05 15:58:33 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			play_victory(t_vm *vm)
{
	if (vm->sounds)
	{
		system("killall afplay");
		system("afplay sounds/victory.wav&");
	}
	return (1);
}

int			play_death(t_vm *vm)
{
	if (vm->sounds && vm->sounds_death)
	{
		system("killall afplay");
		system("afplay sounds/death.wav&");
	}
	return (1);
}
