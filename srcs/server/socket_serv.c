/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_serv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:15:21 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/08 17:15:14 by nrouvroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "online.h"

void	game_start_serv(t_server *serv, struct sockaddr_in *address)
{
	int	i;
	int	j;

	(void)address;
	printf("Starting the game\n");
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		ft_memcpy(serv->buffer, "Starting the game\n\0", 25);
		send(serv->client_socket[i], serv->buffer, O_BUFFSIZE, 0);
		j = -1;
		while (++j < MAX_PLAYERS)
		{
			ft_memcpy(serv->buffer, serv->champ[j].filename, O_BUFFSIZE);
			send(serv->client_socket[i], serv->buffer, O_BUFFSIZE, 0);
			ft_memcpy(serv->buffer, serv->champ[j].code, O_BUFFSIZE);
			send(serv->client_socket[i], serv->buffer, O_BUFFSIZE, 0);
		}
	}
}

void	ft_init_serv(t_server *serv, struct sockaddr_in *address, int *i)
{
	*i = -1;
	while (++(*i) <= MAX_PLAYERS)
	{
		serv->client_socket[*i] = 0;
		ft_memset(serv->champ[*i].filename, 0, MAX_O_SIZ);
		ft_memset(serv->champ[*i].code, 0, MAX_O_SIZ);
	}
	if ((serv->master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		ft_o_exit("\nERROR : creating the socket\n");
	serv->opt = TRUE;
	if (setsockopt(serv->master_socket, SOL_SOCKET, SO_REUSEADDR,
				(char *)&serv->opt, sizeof(serv->opt)) < 0)
		ft_o_exit("\nERROR : fixing the port\n");
	ft_memset(&(*address), '0', sizeof(*address));
	ft_memset(serv->buffer, '0', O_BUFFSIZE);
	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(PORT);
	if (bind(serv->master_socket, (struct sockaddr*)address,
				sizeof(*address)) < 0)
		ft_o_exit("\nERROR : bind failed\n");
	if (listen(serv->master_socket, (MAX_PLAYERS + 1) * 4) < 0)
		ft_o_exit("\nERROR : Failed to listen\n");
	serv->addrlen = (socklen_t)(sizeof(*address));
}

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
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (serv->client_socket[i] == 0)
		{
			serv->client_socket[i] = serv->new_socket;
			printf("player %d connected \n", i);
			ft_memcpy(serv->buffer, "you are now connected as player [\0", 35);
			ft_strcat((char*)serv->buffer, ft_itoa(i));
			ft_strcat((char*)serv->buffer, "]");
			send(serv->new_socket, serv->buffer, O_BUFFSIZE, 0);
			break ;
		}
	}
	if (i == MAX_PLAYERS)
	{
		strcpy((char*)serv->buffer, "ERROR : too many players\0");
		send(serv->new_socket, serv->buffer, 30, 0);
		close(serv->new_socket);
	}
}

void	ft_get_msg(t_server *serv, struct sockaddr_in *address, int i)
{
	int	j;

	getpeername(serv->sd, (struct sockaddr*)address, &(serv->addrlen));
	serv->buffer[serv->n] = 0;
	if (serv->champ[i].filename[0] == 0)
		ft_memcpy(serv->champ[i].filename, serv->buffer, MAX_O_SIZ);
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

void	ft_find_fd(t_server *serv, struct sockaddr_in *address, int i)
{
	serv->sd = serv->client_socket[i];
	if (FD_ISSET(serv->sd, &(serv->readfds)))
	{
		if ((serv->n = read(serv->sd, serv->buffer, MAX_O_SIZ)) == 0)
		{
			getpeername(serv->sd, (struct sockaddr*)address, &(serv->addrlen));
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
	int					i;
	struct sockaddr_in	address;
	t_server			serv;

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
							(struct sockaddr*)&address, &serv.addrlen)) < 0)
				ft_o_exit("\nERROR : accept failed\n");
			ft_new_co(&serv);
		}
		i = -1;
		while (++i < MAX_PLAYERS)
			ft_find_fd(&serv, &address, i);
	}
	return (0);
}
