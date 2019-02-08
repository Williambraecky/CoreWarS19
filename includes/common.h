/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:24:36 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/08 16:27:42 by sde-spie         ###   ########.fr       */
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
typedef struct s_cham	t_cham;

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
unsigned int	n_bytes_to_uint(unsigned char *header, unsigned int nbr);
#endif
