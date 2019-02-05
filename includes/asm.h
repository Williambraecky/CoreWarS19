/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/05 15:42:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** Includes
*/

# include "common.h"

/*
** Defines
*/

# define ASM_BUFFER_SIZE 2048
# define CODE_MAX_START CHAMP_MAX_SIZE
# define TOKEN_SIZE_START 50
# define SEPARATOR_CHARS " \n\t\r,"

/*
** Flags
*/

# define COMMENT_FLAG 1 << 0
# define COMMENT_TOO_LONG 1 << 1
# define NAME_FLAG 1 << 2
# define NAME_TOO_LONG 1 << 3
# define END_SYNTAX_ERR 1 << 4

/*
** Typedefs
*/

typedef struct s_asm	t_asm;
typedef struct s_label	t_label;
typedef struct s_repl	t_repl;
typedef struct s_token	t_token;
typedef struct s_pos	t_pos;
typedef enum e_type		t_type;
typedef struct s_define	t_define;

/*
** Structures
*/

enum		e_type
{
	MEM_ERROR = 0,
	LEX_ERROR = 1,
	ENDLINE = 2,
	COMMAND_NAME = 4,
	COMMAND_COMMENT = 8,
	STRING = 16,
	LABEL = 32,
	INSTRUCTION = 64,
	REGISTER = 128,
	DIRECT = 256,
	DIRECT_LABEL = 512,
	INDIRECT = 1024,
	INDIRECT_LABEL = 2048,
	SEPARATOR = 4096,
	COMMENT = 8192,
	END = 16384,
};

struct		s_asm
{
	int		flags;
	int		fd;
	int		line;
	char	*filename;
	char	*file;
	int		file_size;
	t_token	*tokens;
	size_t	nb_tokens;
	size_t	max_tokens;
	t_repl	*replace;
	size_t	nb_replace;
	t_label	*labels;
	size_t	nb_labels;
	t_cham	champ;
	t_u8	*code;
	size_t	current_code_max;
};

struct		s_pos
{
	int		x;
	int		y;
};

struct		s_token
{
	t_pos	pos;
	size_t	size;
	t_type	type;
	char	*string;
};

struct		s_repl
{
	char	*name;
	int		position;
	int		code_pos;
	int		label_size;
	t_token	token;
};

struct		s_label
{
	char	*name;
	int		position;
};

/*
** Used for the lexer
*/

struct		s_define
{
	t_type	type;
	int		(*is_of_type)(char *line, size_t i);
	t_token	(*make_token)(char *line, size_t i);
};

/*
** Prototypes
*/

void		free_asm(t_asm *asm_t);
void		exit_error(t_asm *asm_t, char *error);
int			asm_add_label(t_asm *asm_t, char *name, int position);
int			asm_add_replace(t_asm *asm_t, t_repl label);
t_label		*get_label(t_asm *asm_t, char *name);
void		asm_parse(t_asm *asm_t);
char		*read_property(t_asm *asm_t, char *line);
int			strtrimset(char **str);
void		syntax_error(t_asm *asm_t, t_token token);
void		lexical_error(t_asm *asm_t, t_pos pos);
void		invalid_instruction_error(t_asm *asm_t, t_token token);
int			has_unfinished_quote(char *str);
int			str_is_number(char *str);
void		gnl_to_one_string(t_asm *asm_t);
void		code_write_byte(t_asm *asm_t, t_u8 byte);
void		code_write_bytes(t_asm *asm_t, t_u8 *bytes, size_t size);
char		*first_non_space(char *str);
char		*type_get_string(t_type type);
void		asm_add_token(t_asm *asm_t, t_token token);
t_pos		str_calc_pos(char *str, size_t i);
void		asm_token_parse(t_asm *asm_t);
t_u8		gen_code_octet(t_asm *asm_t, size_t pos);
int			instruction_check_param(t_op *op, t_token param, int param_count);
void		invalid_parameter_type_error(t_asm *asm_t,
	int param_count, t_type type, char *op_name);
char		*get_error_string_for_type(t_type type);
void		process_parameter(t_asm *asm_t, t_token parameter, int label_size,
	int instruction_pos);
void		asm_replace_labels(t_asm *asm_t);

/*
** Token prototypes
*/

int			end_of_type(char *line, size_t i);
t_token		end_make_token(char *line, size_t i);
int			name_of_type(char *line, size_t i);
t_token		name_make_token(char *line, size_t i);
void		process_name(t_asm *asm_t, t_token token, size_t *i);
int			comment_of_type(char *line, size_t i);
t_token		comment_make_token(char *line, size_t i);
void		process_comment(t_asm *asm_t, t_token token, size_t *i);
int			separator_of_type(char *line, size_t i);
t_token		separator_make_token(char *line, size_t i);
int			string_of_type(char *line, size_t i);
t_token		string_make_token(char *line, size_t i);
int			label_of_type(char *line, size_t i);
t_token		label_make_token(char *line, size_t i);
void		process_label(t_asm *asm_t, t_token token, size_t *i);
int			register_of_type(char *line, size_t i);
t_token		register_make_token(char *line, size_t i);
void		process_register(t_asm *asmt_t, t_token token);
int			direct_of_type(char *line, size_t i);
t_token		direct_make_token(char *line, size_t i);
void		process_direct(t_asm *asmt_t, t_token token, int label_size);
int			dlabel_of_type(char *line, size_t i);
t_token		dlabel_make_token(char *line, size_t i);
void		process_dlabel(t_asm *asmt_t, t_token token, int label_size,
	int instruction_pos);
int			indirect_of_type(char *line, size_t i);
t_token		indirect_make_token(char *line, size_t i);
void		process_indirect(t_asm *asmt_t, t_token token);
int			ilabel_of_type(char *line, size_t i);
t_token		ilabel_make_token(char *line, size_t i);
void		process_ilabel(t_asm *asm_t, t_token token, int instruction_pos);
int			instruction_of_type(char *line, size_t i);
t_token		instruction_make_token(char *line, size_t i);
void		process_instruction(t_asm *asm_t, t_token token, size_t *i);
int			endline_of_type(char *line, size_t i);
t_token		endline_make_token(char *line, size_t i);

#endif
