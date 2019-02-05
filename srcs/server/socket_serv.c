/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_serv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:15:21 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/01/31 04:14:22 by nrouvroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "online.h"

void	game_start(t_server serv, struct sockaddr_in address)
{
	int i;

	(void)address;
	printf("Starting the game\n");
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		ft_strcpy(serv.buffer, "Starting the game\n\0");
		send(serv.client_socket[i], serv.buffer, O_BUFFSIZE, 0);
		usleep(25000);
	}
}

int main(void)
{
	int	i;
	int	j;
	struct sockaddr_in	address;
	t_server	serv;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		serv.client_socket[i] = 0;
		ft_memset(serv.client_filename[i], 0, 100);
		ft_memset(serv.client_champion[i], 0, CHAMP_MAX_SIZE);
	}
	if ((serv.master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		ft_o_exit("\nERROR : creating the socket\n");
	printf("socket retreive success\n");
	serv.opt = TRUE;
	if (setsockopt(serv.master_socket, SOL_SOCKET, SO_REUSEADDR ,(char *)&serv.opt, sizeof(serv.opt)) < 0)
		ft_o_exit("\nERROR : fixing the port\n");
	memset(&address, '0', sizeof(address));
	memset(serv.buffer, '0', sizeof(serv.buffer));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if (bind(serv.master_socket, (struct sockaddr*) &address, sizeof(address)) < 0)
		ft_o_exit("\nERROR : bind failed\n");
	printf("Listener on port %d\n", PORT);
	if (listen(serv.master_socket, (MAX_PLAYERS + 1 * 4)) < 0)
		ft_o_exit("\nERROR : Failed to listen\n");
	serv.addrlen = (socklen_t)sizeof(address);
	printf("Waiting for connections\n");
	while (TRUE)
	{
		FD_ZERO(&serv.readfds);
		FD_SET(serv.master_socket, &serv.readfds);
		serv.max_sd = serv.master_socket;
		i = 0;
		while (i < MAX_PLAYERS)
		{
			serv.sd = serv.client_socket[i];
			if (serv.sd > 0)
				FD_SET(serv.sd, &serv.readfds);
			if (serv.sd > serv.max_sd)
				serv.max_sd = serv.sd;
			i++;
		}
		serv.activity = select(serv.max_sd + 1, &serv.readfds, NULL, NULL, NULL);
		if ((serv.activity < 0) && (errno != EINTR))
			printf("\nERROR : select error\n");
		if (FD_ISSET(serv.master_socket, &serv.readfds))
		{
			if ((serv.new_socket = accept(serv.master_socket, (struct sockaddr*) &address, &serv.addrlen)) < 0)
				ft_o_exit("\nERROR : accept failed\n");
			printf("New connection, socket_fd %d, ip %s, port %d\n",serv.new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
						i = 0;
			while (i < MAX_PLAYERS)
			{
				if (serv.client_socket[i] == 0)
				{
					serv.client_socket[i] = serv.new_socket;
					printf("added to our list of sockets as %d\n", i);
					strcpy(serv.msg, "you are now connected as player [\0");
					ft_strcat(serv.msg, ft_itoa(i));
					ft_strcat(serv.msg, "]");
					ft_strcpy(serv.buffer, serv.msg);
					if ((size_t)send(serv.new_socket, serv.buffer, ft_strlen(serv.msg), 0) != ft_strlen(serv.msg))
						printf("\nERROR : confirmation message send\n");
					printf("welcome message sent\n");
					break;
				}
				i++;
			}
			if (i == MAX_PLAYERS)
			{
				strcpy(serv.buffer, "Sorry but the max amount of player is already connected\n\0");
				send(serv.new_socket, serv.buffer, ft_strlen(serv.buffer), 0);
				close(serv.new_socket);
			}
		}
		i = 0;
		while (i < MAX_PLAYERS)
		{
			serv.sd = serv.client_socket[i];
			if (FD_ISSET(serv.sd, &serv.readfds))
			{
				if ((serv.n = read(serv.sd, serv.buffer, O_BUFFSIZE)) == 0)
				{
					getpeername(serv.sd, (struct sockaddr*)&address, &serv.addrlen);
					printf("Client disconnected, ip %s, port %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
					close(serv.sd);
					serv.client_socket[i] = 0;
					ft_memset(serv.client_filename[i], 0, 100);
					ft_memset(serv.client_champion[i], 0, CHAMP_MAX_SIZE);
				}
				else
				{
					getpeername(serv.sd, (struct sockaddr*) &address, &serv.addrlen);
					serv.buffer[serv.n] = 0;
					printf("message received from %d : %s\n", i, serv.buffer);
					if (serv.client_filename[i][0] == 0)
					{
						ft_strcpy(serv.client_filename[i], serv.buffer);
						printf("client filename : %s\n",serv.client_filename[i]);
					}
					else
					{
						printf("champion code for player : %d\n", i);
						j = -1;
						if (!ft_strstr(serv.buffer, "START_CODE_CHAMPION"))
						{
							printf(" buffer: %s\n", serv.buffer);
							ft_o_exit("\nERROR :  client champion code is wrong\n");
						}
						while (serv.n == O_BUFFSIZE && (serv.n = read(serv.sd, serv.buffer, O_BUFFSIZE)) > 0)
						{
							printf(" buffer: %s\n", serv.buffer);
							if (ft_strstr(serv.buffer, "END_CODE_CHAMPION"))
								break;
							j++;
							if (j * O_BUFFSIZE > CHAMP_MAX_SIZE)
								ft_o_exit("\nERROR : Champ too long\n");
							ft_memcpy(serv.client_champion[i] + j * O_BUFFSIZE, serv.buffer, O_BUFFSIZE);
						}
						i = -1;
						while (++i < MAX_PLAYERS)
						if (serv.client_filename[i][0] == 0 || serv.client_champion[i][0] == 0)
							break;
						if (i == MAX_PLAYERS)
							game_start(serv, address);
					}
				}
			}
			i++;
		}
	}
	return (0);
}
