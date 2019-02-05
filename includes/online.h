/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   online.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:14:45 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/01/31 03:05:35 by nrouvroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ONLINE_H
# define ONLINE_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include "common.h"
# include "op.h"

# define PORT 4352
# define O_BUFFSIZE 1024
# define TRUE 1
# define FALSE 0

struct s_server
{
	int					master_socket;
	int					new_socket;
	socklen_t			addrlen;
	int					activity;
	int					client_socket[MAX_PLAYERS];
	char				client_filename[MAX_PLAYERS + 1][100];
	unsigned char		client_champion[MAX_PLAYERS + 1][CHAMP_MAX_SIZE];
	int					sd;
	int					max_sd;
	int					opt;
	int					n;
	char				buffer[O_BUFFSIZE];
	char				msg[500];
	fd_set				readfds;
};

struct s_client
{
	char				filename[100];
	int					playerID;
	int					sockfd;
	struct sockaddr_in	serv_addr;
	char				buffer[O_BUFFSIZE];
};

typedef struct s_server t_server;
typedef struct s_client t_client;
#endif
