/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:30:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/25 17:09:19 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			strtrimset(char **str)
{
	char *new;

	new = ft_strtrim(*str);
	free(*str);
	if (new == NULL)
		return (-1);
	*str = new;
	return (1);
}

static char	*first_non_space(char *str)
{
	while ((*str == ' ' || *str == '\t' || *str == '\r') && *str)
		str++;
	return (str);
}

char		*read_property(t_asm *asm_t, char *line)
{
	size_t	i;
	char	*end;
	char	*ret;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	while (line[i] == ' ' && line[i])
		i++;
	if (!line[i])
	{
		free(line);
		syntax_error(asm_t, (int)i + 1, "ENDLINE", NULL);
	}
	if (line[i] != '\"')
	{
		free(line);
		lexical_error(asm_t, (int)i + 1);
	}
	i++;
	end = ft_strchr(line + i, '\"');
	if (end == NULL)
	{
		free(line);
		syntax_error(asm_t, (int)i, "ENDLINE", NULL);
	}
	if (end + 1 != '\0')
	{
		free(line);
		syntax_error(asm_t, (int)i, *first_non_space(line) == '\"' ? "STRING"
		: "INSTRUCTION", first_non_space(line));
	}
	ret = ft_strsub(line, i, end - line + i);
	return (ret);
}
