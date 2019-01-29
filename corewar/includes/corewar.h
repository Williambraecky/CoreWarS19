/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:34:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/29 16:46:47 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COREWAR_H
# define COREWAR_H
# include "../../libft/includes/libft.h"
# include "op.h"
# include <fcntl.h>

typedef struct		s_process
{
	size_t			index_arena;
	int				index_champ;
	int				cycle;
	char			alive;
	char			instruction;
	int				registre[REG_NUMBER];
	char			PC;
	char			carry;
	int				lives;
	int				lives_since_check;
	int				number;
}					t_process;


typedef struct		s_code
{
	t_header		header;
	unsigned char	prog[CHAMP_MAX_SIZE];
}					t_code;


typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
	char			arena_owner[MEM_SIZE];
	int				cycle_to_die;
	int				cycle_left;
	t_process		*process;
	int				nbr_process;
	int				nbr_process_alive;
}					t_arena;


typedef struct		s_champ
{
	t_code			code;
	int				number;
	int				lives;
}					t_champ;


typedef struct		s_vm
{
	t_champ			champs[MAX_PLAYERS];
	t_arena			arena;
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

/*
** utils.c
*/

int				find_number(t_vm *vm);
unsigned int	n_bytes_to_uint(unsigned char *str, unsigned int nbr);

/*
** read_champ.c
*/

void			read_champ(t_vm *vm, char **argv, int mode);

/*
** prepare_battle.c
*/

void			check_error(t_vm *vm);
void			prepare_battle(t_vm *vm);

/*
** create_process.c
*/

t_process		*create_process(t_vm *vm);

/*
** init_vm.c
*/

void			init_vm(t_vm *vm);

#endif
