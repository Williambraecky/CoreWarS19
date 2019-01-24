/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:34:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/24 18:22:12 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

typedef struct	s_process
{

}				t_process;

typedef struct	s_arena
{
	char		arena[MEM_SIZE];
}				t_arena;

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	int			number;
}				t_champ;

typedef struct	s_vm
{
	t_champ		*champs;
	t_arena		*arena;
	int			dump;
	int			nbr_champ;
}				t_vm;


/*
** parse_command.c
*/

char			**parse_command(t_vm *vm, char ** argv);

/*
** corewar.c
*/

