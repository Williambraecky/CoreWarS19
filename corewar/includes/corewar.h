/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:34:21 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/01 20:26:05 by sde-spie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COREWAR_H
# define COREWAR_H
# include "../../libft/includes/libft.h"
# include "op.h"
# include "struct.h"
# include <fcntl.h>
# include <curses.h>
# include <term.h>


typedef char		t_arg_type;
typedef struct		s_instruct
{
	char			op_code;
	void			(*op)();
	int				cycle_exec;
	int				nb_arg;
	t_arg_type		types[3];
	t_arg_type		value[3];
}					t_instruct;


typedef struct		s_process
{
	size_t			index_arena;
	int				index_champ;
	char			alive;
	t_instruct		instruction;
	int				registre[REG_NUMBER];
	int				pc;
	char			carry;
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
	int				cycle_since_check;
	t_process		*process;
	int				nbr_process;
	int				nbr_process_alive;
	int				lives_since_last_check;
	int				check_count;
	int				winner;
}					t_arena;


typedef struct		s_champ
{
	t_code			code;
	int				number;
	int				lives;
	int				lives_since_last_check;
}					t_champ;


typedef struct		s_vm
{
	t_champ			champs[MAX_PLAYERS];
	t_arena			arena;
	int				dump;
	int				nbr_champ;
	int				n;
	int				visu;
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

//t_process		*create_process(t_vm *vm);
void			set_process(t_vm *vm, t_process *process);

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
** op.c
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

/*
** op_get_params.c
*/

void			op_get_params(t_vm *vm, t_process *process);

/*
** cycle_check.c
*/

void			check_end_cycle(t_vm *vm);

/*
** free.c
*/

void			free_all(t_vm *vm);

/*
** visu.c
*/

void			init_visu(WINDOW **window);
void			print_visu(t_vm *vm, WINDOW **window, int mode);

void			print_19(WINDOW *window);
void			print_19ai(WINDOW *window);
void			print_data(t_vm *vm, WINDOW *window);
void			print_winner(t_vm *vm, WINDOW *window);
void			print_header(t_vm *vm, WINDOW *window);
void			print_memory(t_vm *vm, WINDOW *window);

#endif
