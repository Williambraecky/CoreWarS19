/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_serv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:15:21 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/28 15:41:25 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "online.h"

void	ft_set_fd(t_server *serv)
{
	int	i;

	FD_ZERO(&(serv->readfds));
	FD_SET(serv->master_socket, &(serv->readfds));
	serv->maxsd = serv->master_socket;
	i = 0;
	while (i <= MAX_PLAYERS)
	{
		serv->sd = serv->client_socket[i];
		if (serv->sd > 0)
			FD_SET(serv->sd, &(serv->readfds));
		if (serv->sd > serv->maxsd)
			serv->maxsd = serv->sd;
		i++;
	}
}

void	ft_new_co(t_server *serv)
{
	char	*inbr;
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (serv->client_socket[i] == 0)
		{
			serv->client_socket[i] = serv->new_socket;
			printf("player %d connected \n", i);
			ft_memcpy(serv->buffer, "you are now connected as player [\0", 35);
			inbr = ft_itoa(i);
			ft_strcat((char*)serv->buffer, inbr);
			free(inbr);
			ft_strcat((char*)serv->buffer, "]");
			send(serv->new_socket, serv->buffer, O_BUFFSIZE, 0);
			break ;
		}
	}
	if (i == MAX_PLAYERS)
	{
		ft_strcpy((char*)serv->buffer, "ERROR : too many players\0");
		send(serv->new_socket, serv->buffer, 30, 0);
		close(serv->new_socket);
	}
}

void	ft_get_msg(t_server *serv, t_sockaddr_in *address, int i)
{
	int	j;

	getpeername(serv->sd, (t_sockaddr*)address, &(serv->addrlen));
	serv->buffer[serv->n] = 0;
	if (serv->champ[i].filename[0] == 0)
		ft_get_champ_filename(serv, i);
	else
	{
		if (!ft_strstr((char*)serv->buffer, "START_CODE_CHAMPION"))
			ft_o_exit("\nERROR :  client champion code is wrong\n");
		while ((serv->n = read(serv->sd, serv->buffer, MAX_O_SIZ)) > 0)
		{
			if (ft_strstr((char*)serv->buffer, "END_CODE_CHAMPION"))
				break ;
			ft_memcpy(serv->champ[i].code, serv->buffer, O_BUFFSIZE);
		}
		j = -1;
		while (++j < MAX_PLAYERS)
			if (serv->champ[j].filename[0] == 0 ||
					serv->champ[j].code[2] == 0xea)
				break ;
		if (j == MAX_PLAYERS)
			game_start_serv(serv, address);
	}
}

void	ft_find_fd(t_server *serv, t_sockaddr_in *address, int i)
{
	serv->sd = serv->client_socket[i];
	if (FD_ISSET(serv->sd, &(serv->readfds)))
	{
		if ((serv->n = read(serv->sd, serv->buffer, MAX_O_SIZ)) == 0)
		{
			getpeername(serv->sd, (t_sockaddr*)address, &(serv->addrlen));
			close(serv->sd);
			serv->client_socket[i] = 0;
			ft_memset(serv->champ[i].filename, 0, MAX_O_SIZ);
			ft_memset(serv->champ[i].code, 0, MAX_O_SIZ);
		}
		else
			ft_get_msg(serv, address, i);
	}
}

int		main(void)
{
	int				i;
	t_sockaddr_in	address;
	t_server		serv;

	ft_init_serv(&serv, &address, &i);
	while (TRUE)
	{
		ft_set_fd(&serv);
		serv.activity = select(serv.maxsd + 1, &serv.readfds, NULL, NULL, NULL);
		if ((serv.activity < 0) && (errno != EINTR))
			printf("\nERROR : select error\n");
		if (FD_ISSET(serv.master_socket, &serv.readfds))
		{
			if ((serv.new_socket = accept(serv.master_socket,
							(t_sockaddr*)&address, &serv.addrlen)) < 0)
				ft_o_exit("\nERROR : accept failed\n");
			ft_new_co(&serv);
		}
		i = -1;
		while (++i < MAX_PLAYERS)
			ft_find_fd(&serv, &address, i);
	}
	return (0);
}
