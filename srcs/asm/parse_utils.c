/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:30:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 13:13:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Trim string and assign it to pointer
*/

int		strtrimset(char **str)
{
	char *new;

	new = ft_strtrim(*str);
	free(*str);
	if (new == NULL)
		return (-1);
	*str = new;
	return (1);
}

/*
** Process if the string has an unfinished quote
*/

int		has_unfinished_quote(char *str)
{
	char	*tmp;

	if (!str)
		return (0);
	tmp = ft_strchr(str, '\"');
	if (!tmp)
		return (0);
	tmp = ft_strchr(tmp + 1, '\"');
	if (!tmp)
		return (1);
	return (has_unfinished_quote(tmp + 1));
}

/*
** Returns a pointer to the first non space character in a string
*/

char	*first_non_space(char *str)
{
	while ((*str == ' ' || *str == '\t' || *str == '\r') && *str)
		str++;
	return (str);
}

/*
** libft has strisbumber but it doesn't stop at the first non number
*/

int		str_is_number(char *str)
{
	if (*str == '-' && ft_isdigit(*(str + 1)))
		return (1);
	return (ft_isdigit(*str));
}

t_pos	str_calc_pos(char *str, size_t i)
{
	t_pos	pos;
	size_t	j;

	pos.x = 1;
	pos.y = 1;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\n')
		{
			pos.x = 1;
			pos.y++;
		}
		else
			pos.x++;
		j++;
	}
	return (pos);
}
