/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:52:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/26 17:41:07 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** C'est pas bon du tout je vais devoir refaire
** TODO: Lire tout le fichier d'un coup et créer un array de token
** C'est pas faisable par ligne a cause des commentaires
*/

static char		*handle_join(char **ret, char *tmp)
{
	char	*tmp2;
	size_t	nb_copy;

	if (ft_strchr(tmp, '#')
		&& !has_unfinished_quote(tmp) && !has_unfinished_quote(*ret))
		nb_copy = ft_strchr(tmp, '#') - tmp;
	else
		nb_copy = ft_strlen(tmp);
	if (!(*ret))
		return (ft_strndup(tmp, nb_copy));
	tmp[nb_copy] = '\0';
	tmp2 = ft_strtrijoin(*ret, "\n", tmp);
	return (tmp2);
}
/*
** TODO: Don't copy after comment
*/

static int		read_next_line(t_asm *asm_t, char **ret)
{
	char	*tmp;
	char	*tmp2;
	int		gnl_ret;

	while ((*ret == NULL || has_unfinished_quote(*ret)) &&
		(gnl_ret = get_next_line(asm_t->fd, &tmp)) == 1)
	{
		asm_t->line++;
		tmp2 = handle_join(ret, tmp);
		ft_strdel(&tmp);
		if (!tmp2)
			return (-1);
		ft_strdel(ret);
		*ret = tmp2;
	}
	if (has_unfinished_quote(*ret))
		return (-1);
	return (gnl_ret);
}

static t_type	get_type(char *line, size_t i)
{
	if (ft_strstartswith(line + i, ".name"))
		return (COMMAND_NAME);
	else if (ft_strstartswith(line + i, ".comment"))
		return (COMMAND_COMMENT);
	else if (line[i] == ',')
		return (SEPARATOR);
	else if (line[i] == '\"')
		return (STRING);
	else if (line[i] == 'r' && str_is_number(line + i + 1))
		return (REGISTER);
	else if (str_is_number(line + i))
		return (INDIRECT);
	else if (line[i] == DIRECT_CHAR && line[i + 1] == LABEL_CHAR &&
			str_is_number(line + i + 2))
		return (DIRECT_LABEL);
	else if (line[i] == DIRECT_CHAR && str_is_number(line + i + 1))
		return (DIRECT);
	else if (line[i] == '\0')
		return (ENDLINE);
	//TODO: validate labels if has : -> label else instruction
	return (LEX_ERROR);
}

static void		asm_parse_line(t_asm *asm_t, char *line)
{
	size_t	i;
	t_type	type;

	i = 0;
	(void)asm_t;
	type = get_type(line, i);
	ft_printf("TYPE %d\n", type);
}

int				asm_parse(t_asm *asm_t)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = read_next_line(asm_t, &line)))
	{
		if (strtrimset(&line) == -1)
			exit_error(asm_t, "Out of memory");
		ft_putendl(line);
		asm_parse_line(asm_t, line);
		//TODO: parse per argument
		ft_strdel(&line);
	}
	if (ret == -1)
	{
		ft_strdel(&line);
		exit_error(asm_t, "Error while reading file");
	}
	return (1);
}
