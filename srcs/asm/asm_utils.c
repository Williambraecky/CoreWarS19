/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:55:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/25 15:05:15 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Add unknown label to be replaced at the end of parsing
*/

int		asm_add_replace(t_asm *asm_t, char *name, int position)
{
	t_label	label;
	t_label	*new;

	if (!name)
		return (-1);
	label.name = name;
	label.position = position;
	if (!(new = ft_realloc(asm_t->replace, sizeof(t_label) * asm_t->nb_replace,
		sizeof(t_label) * (asm_t->nb_replace + 1))))
		return (-1);
	new[asm_t->nb_replace++] = label;
	free(asm_t->labels);
	asm_t->replace = new;
	return (1);
}

/*
** Add label to label array
*/

int		asm_add_label(t_asm *asm_t, char *name, int position)
{
	t_label	label;
	t_label	*new;

	if (!name)
		return (-1);
	label.name = name;
	label.position = position;
	if (!(new = ft_realloc(asm_t->labels, sizeof(t_label) * asm_t->nb_labels,
		sizeof(t_label) * (asm_t->nb_labels + 1))))
		return (-1);
	new[asm_t->nb_labels++] = label;
	free(asm_t->labels);
	asm_t->labels = new;
	return (1);
}

/*
** Returns label if it exists or null if it doesn't
*/

t_label	*get_label(t_asm *asm_t, char *name)
{
	size_t i;

	i = 0;
	while (i < asm_t->nb_labels)
	{
		if (ft_strcmp(asm_t->labels[i].name, name) == 0)
			return (&(asm_t->labels[i]));
		i++;
	}
	return (NULL);
}
