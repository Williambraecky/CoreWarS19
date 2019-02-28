/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:01:41 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/02/28 15:48:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
** Reverse byte order of 32 bit integer
** Order of operations:
** byte 3 to byte 0
** byte 1 to byte 2
** byte byte 2 to byte 1
** byte 0 to byte 3
*/

int		reverse_int32(int i)
{
	return (((i >> 24) & 0x000000ff)
			| ((i << 8) & 0x00ff0000)
			| ((i >> 8) & 0x0000ff00)
			| ((i << 24) & 0xff000000));
}

short	reverse_int16(short s)
{
	return (s << 8 | s >> 8);
}

t_u32	n_bytes_to_uint(t_u8 *header, t_u32 nbr)
{
	t_u32		i;
	t_u32		ret;
	t_u32		mask;

	ret = 0;
	if (nbr > 4)
		exit(0);
	i = 0;
	while (i < nbr)
	{
		ret = ret << 8;
		mask = (t_u32)*header;
		ret = ret | mask;
		header++;
		i++;
	}
	return (ret);
}
