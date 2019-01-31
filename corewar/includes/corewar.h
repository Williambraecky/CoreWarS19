/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:34:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/01/31 11:36:15 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COREWAR_H
# define COREWAR_H
# define MAX_NBR_ARGS	4
# include "../../libft/includes/libft.h"
# include "op.h"
# include <fcntl.h>

typedef char		t_arg_type;

typedef struct		s_process
{
	size_t			index_arena;
	int				index_champ;
	int				cycle;
	char			alive;
	t_instruct		instruction;
	int				registre[REG_NUMBER];
	int				pc;
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
	int				total_cycle;
	int				cycle_to_die;
	int				cycle_since_check;;
	t_process		*process;
	int				nbr_process;
	int				nbr_process_alive;
	int				winner;
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

typedef struct		s_instruct
{
	char			op_code;
	void			(*op)(t_vm *, t_process *);
	int				cycle_exec;
	int				nb_arg;
	t_arg_type		types[3];
	int				unknown;
	int				code_octet; //A valider
	int				unknown3;
}					t_instruct;

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
int				dump_check(t_vm vm);

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


/*
 ** introduce_champs.c
 */

void			introduce_champs(t_vm vm);

/*
 ** do_cycle.c
 */

void			do_cycle(t_vm *vm);

/*
 ** read_instruction.c
 */

t_instruct		read_instruction(t_vm *vm, int pc);

/*
** instructions.c
*/

void			op_null(t_vm *vm, t_process *process);
void			op_live(t_vm *vm, t_process *process);
void			op_ld(t_vm *vm, t_process *process);
void			op_st(t_vm *vm, t_process *process);
void			op_add(t_vm *vm, t_process *process);
void			op_sub(t_vm *vm, t_process *process);
void			op_and(t_vm *vm, t_process *process);
void			op_or(t_vm *vm, t_process *process);
void			op_xor(t_vm *vm, t_process *process);
void			op_zjmp(t_vm *vm, t_process *process);
void			op_ldi(t_vm *vm, t_process *process);
void			op_sti(t_vm *vm, t_process *process);
void			op_fork(t_vm *vm, t_process *process);
void			op_lld(t_vm *vm, t_process *process);
void			op_lldi(t_vm *vm, t_process *process);
void			op_lfork(t_vm *vm, t_process *process);
void			op_aff(t_vm *vm, t_process *process);

#endif
