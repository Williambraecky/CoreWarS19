/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   online.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:14:45 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/06 23:10:30 by nrouvroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ONLINE_H
# define ONLINE_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include "libft.h"
# include "common.h"
# include "op.h"

# define PORT 4352
# define TRUE 1
# define FALSE 0
# define MAX_O_SIZ CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16
# define O_BUFFSIZE MAX_O_SIZ

struct s_o_champ
{
	unsigned char		filename[MAX_O_SIZ];
	unsigned char		code[MAX_O_SIZ];
};

typedef struct s_o_champ t_o_champ;

struct s_server
{
	int					master_socket;
	int					new_socket;
	socklen_t			addrlen;
	int					activity;
	int					client_socket[MAX_PLAYERS + 1];
	t_o_champ			champ[MAX_PLAYERS + 1];
	int					sd;
	int					maxsd;
	int					opt;
	int					n;
	unsigned char		buffer[O_BUFFSIZE];
	char				msg[500];
	fd_set				readfds;
};

struct s_client
{
	t_o_champ			champ[MAX_PLAYERS + 1];
	int					sockfd;
	struct sockaddr_in	serv_addr;
	unsigned char		buffer[O_BUFFSIZE];
};

typedef struct s_server t_server;
typedef struct s_client t_client;

void	ft_client_1(t_client client);
void	ft_client_2(t_client client);
#endif
