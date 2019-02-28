/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_serv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:30:43 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/28 15:43:17 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "online.h"

void	ft_get_champ_filename(t_server *serv, int i)
{
	int		inds;
	int		tr;
	int		ind;

	tr = 0;
	ind = -1;
	inds = 0;
	while (serv->buffer[++ind] != 0)
	{
		if (serv->buffer[ind] == '/')
		{
			inds = ind + 1;
			tr = 1;
		}
	}
	serv->buffer[ind - 4] = i + 48;
	serv->buffer[ind - 3] = '.';
	serv->buffer[ind - 2] = 'c';
	serv->buffer[ind - 1] = 'o';
	serv->buffer[ind] = 'r';
	serv->buffer[ind + 1] = '\0';
	ft_memcpy(serv->champ[i].filename, serv->buffer + inds, 250);
}

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
			usleep(25000);
			ft_memcpy(serv->buffer, serv->champ[j].code, O_BUFFSIZE);
			send(serv->client_socket[i], serv->buffer, O_BUFFSIZE, 0);
			usleep(25000);
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
	if (bind(serv->master_socket, (t_sockaddr*)address,
				sizeof(*address)) < 0)
		ft_o_exit("\nERROR : bind failed\n");
	if (listen(serv->master_socket, (MAX_PLAYERS + 1) * 4) < 0)
		ft_o_exit("\nERROR : Failed to listen\n");
	serv->addrlen = (socklen_t)(sizeof(*address));
}
