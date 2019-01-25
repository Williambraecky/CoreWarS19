/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:34:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/25 17:08:42 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COREWAR_H
# define COREWAR_H
# include "../../libft/includes/libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct		s_process
{

}					t_process;

typedef struct		s_code
{
	t_header		header;
	unsigned char	prog[CHAMP_MAX_SIZE];
}					t_code;

typedef struct		s_arena
{
	char			arena[MEM_SIZE];
}					t_arena;

typedef struct		s_champ
{
	t_code			code;
	int				number;
}					t_champ;

typedef struct		s_vm
{
	t_champ			champs[MAX_PLAYERS];
	t_arena			*arena;
	int				dump;
	int				nbr_champ;
	int				n;
}					t_vm;


/*
** parse_command.c
*/

char			**parse_command(t_vm *vm, char ** argv);

/*
** corewar.c
*/


/*
** error.c
*/

void			error_exit(t_vm *vm, char *txt);
int				error_usage(void);

int				find_number(t_vm *vm);
unsigned int	n_bytes_to_uint(unsigned char *str, unsigned int nbr);

void		read_champ(t_vm *vm, char **argv, int mode);
#endif
