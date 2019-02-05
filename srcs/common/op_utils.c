/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:54:35 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 13:54:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

extern t_op	g_op_tab[17];

t_op	*get_op(char *str)
{
	size_t	i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(g_op_tab[i].name, str))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}
