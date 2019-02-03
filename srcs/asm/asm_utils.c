/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:55:22 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/03 14:12:32 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Add unknown label to be replaced at the end of parsing
** NOTE: replace name is not duplicated
*/

int		asm_add_replace(t_asm *asm_t, t_label label)
{
	t_label	*new;

	if (!label.name)
		exit_error(asm_t, "Out of memory");
	if (!(new = ft_realloc(asm_t->replace, sizeof(t_label) * asm_t->nb_replace,
		sizeof(t_label) * (asm_t->nb_replace + 1))))
		exit_error(asm_t, "Out of memory");
	new[asm_t->nb_replace++] = label;
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

	if (!name || !(label.name = ft_strdup(name)))
		exit_error(asm_t, "Out of memory");
	label.position = position;
	if (!(new = ft_realloc(asm_t->labels, sizeof(t_label) * asm_t->nb_labels,
		sizeof(t_label) * (asm_t->nb_labels + 1))))
		exit_error(asm_t, "Out of memory");
	new[asm_t->nb_labels++] = label;
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
		if (ft_strcmp(asm_t->labels[i].name, name) == 0
			|| (ft_strstartswith(asm_t->labels[i].name, name)
			&& asm_t->labels[i].name[ft_strlen(name)] == ':'))
			return (&(asm_t->labels[i]));
		i++;
	}
	return (NULL);
}
