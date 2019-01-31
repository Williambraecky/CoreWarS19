/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:24:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/31 13:55:05 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "op.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef unsigned char	t_u8;
typedef struct s_champ	t_champ;

struct			s_champ
{
	t_header	header;
	t_u8		code[CHAMP_MAX_SIZE + 1]; // + 1 just in case
};

/*
** Utils
*/

int				reverse_int32(int i);
short			reverse_int16(short s);
t_op			*get_op(char *str);

#endif
