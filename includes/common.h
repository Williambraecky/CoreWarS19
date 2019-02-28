/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:24:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/28 15:47:21 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

/*
** Includes
*/

# include "op.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

/*
** Typedefs
*/

typedef unsigned char	t_u8;
typedef unsigned int	t_u32;
typedef struct s_cham	t_cham;

/*
** Structures
*/

struct			s_cham
{
	t_header	header;
	t_u8		code[CHAMP_MAX_SIZE + 1];
};

/*
** Utils
*/

void			ft_o_exit(char *str);
int				reverse_int32(int i);
short			reverse_int16(short s);
t_op			*get_op(char *str);
t_u32			n_bytes_to_uint(t_u8 *header, t_u32 nbr);

#endif
