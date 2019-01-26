/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:23:40 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/26 17:07:59 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** Includes
*/

# include "common.h"

/*
** Typedefs
*/

typedef struct s_asm	t_asm;
typedef struct s_label	t_label;
typedef struct s_token	t_token;
typedef struct s_pos	t_pos;
typedef enum e_type		t_type;

/*
** Structures
*/

enum		e_type
{
	LEX_ERROR = 1,
	ENDLINE = 2,
	COMMAND_NAME = 4,
	COMMAND_COMMENT = 8,
	STRING = 16,
	INSTRUCTION = 32,
	LABEL = 64,
	REGISTER = 128,
	DIRECT = 256,
	DIRECT_LABEL = 512,
	INDIRECT = 1024,
	SEPARATOR = 2048
};

struct		s_asm
{
	int		fd;
	int		has_name;
	int		has_description;
	int		line;
	t_label	*replace;
	size_t	nb_replace;
	t_label	*labels;
	size_t	nb_labels;
	t_champ	champ;
};

struct		s_pos
{
	int		x;
	int		y;
};

struct		s_label
{
	char	*name;
	int		position; //maybe not size_t
};

struct		s_token
{
	t_pos	pos;
	t_type	type;
	char	*string;
};

/*
** Prototypes
*/

void		free_asm(t_asm *asm_t);
void		exit_error(t_asm *asm_t, char *error);
void		exit_usage(char *prog_name);
int			asm_add_label(t_asm *asm_t, char *name, int position);
t_label		*get_label(t_asm *asm_t, char *name);
int			asm_parse(t_asm *asm_t);
char		*read_property(t_asm *asm_t, char *line);
int			strtrimset(char **str);
void		syntax_error(t_asm *asm_t, int column, char *type, char *addition);
void		lexical_error(t_asm *asm_t, int column);
int			has_unfinished_quote(char *str);
int			str_is_number(char *str);

#endif
