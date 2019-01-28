/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/28 17:13:43 by wbraeckm         ###   ########.fr       */
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
# define SEPARATOR_CHARS " \n\t\r,"

/*
** Typedefs
*/

typedef struct s_asm	t_asm;
typedef struct s_label	t_label;
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
	SEPARATOR = 2048,
	COMMENT = 4096,
	END = 8192
};

struct		s_asm
{
	int		fd;
	int		line;
	char	*file;
	int		file_size;
	t_label	*replace;
	size_t	nb_replace;
	t_label	*labels;
	size_t	nb_labels;
	t_champ	champ;
	t_u8	*code;
	size_t	current_code_max;
};

struct		s_pos
{
	int		x;
	int		y;
};

struct		s_label
{
	char	*name;
	int		position;
};

struct		s_token
{
	t_pos	pos;
	size_t	size;
	t_type	type;
	char	*string;
};

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
void		exit_usage(char *prog_name);
int			asm_add_label(t_asm *asm_t, char *name, int position);
t_label		*get_label(t_asm *asm_t, char *name);
void		asm_parse(t_asm *asm_t);
char		*read_property(t_asm *asm_t, char *line);
int			strtrimset(char **str);
void		syntax_error(t_asm *asm_t, int column, char *type, char *addition);
void		lexical_error(t_asm *asm_t, int column);
int			has_unfinished_quote(char *str);
int			str_is_number(char *str);
void		gnl_to_one_string(t_asm *asm_t);
void		code_write_byte(t_asm *asm_t, t_u8 byte);
void		code_write_bytes(t_asm *asm_t, t_u8 *bytes, size_t size);
char		*first_non_space(char *str);

/*
** Define prototypes
*/

int			end_of_type(char *line, size_t i);
t_token		end_make_token(char *line, size_t i);
int			name_of_type(char *line, size_t i);
t_token		name_make_token(char *line, size_t i);
int			comment_of_type(char *line, size_t i);
t_token		comment_make_token(char *line, size_t i);
int			separator_of_type(char *line, size_t i);
t_token		separator_make_token(char *line, size_t i);
int			string_of_type(char *line, size_t i);
t_token		string_make_token(char *line, size_t i);
int			label_of_type(char *line, size_t i);
t_token		label_make_token(char *line, size_t i);
int			register_of_type(char *line, size_t i);
t_token		register_make_token(char *line, size_t i);
int			direct_of_type(char *line, size_t i);
t_token		direct_make_token(char *line, size_t i);
int			dlabel_of_type(char *line, size_t i);
t_token		dlabel_make_token(char *line, size_t i);
int			indirect_of_type(char *line, size_t i);
t_token		indirect_make_token(char *line, size_t i);
int			instruction_of_type(char *line, size_t i);
t_token		instruction_make_token(char *line, size_t i);
int			endline_of_type(char *line, size_t i);
t_token		endline_make_token(char *line, size_t i);

#endif
