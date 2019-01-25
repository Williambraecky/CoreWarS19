/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:24:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/01/25 13:34:13 by wbraeckm         ###   ########.fr       */
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
	t_u8		code[CHAMP_MAX_SIZE];
};

/*
** Utils
*/

int				reverse_int32(int i);
short			reverse_int16(short s);

#endif
