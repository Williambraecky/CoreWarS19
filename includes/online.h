/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   online.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:14:45 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/28 15:41:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONLINE_H
# define ONLINE_H

/*
** Includes
*/

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include "libft.h"
# include "common.h"
# include "op.h"

/*
** Defines
*/

# define PORT 4352
# define TRUE 1
# define FALSE 0
# define MAX_O_SIZ CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16
# define O_BUFFSIZE MAX_O_SIZ

/*
** Typedefs
*/

typedef struct s_o_champ	t_o_champ;
typedef struct s_server		t_server;
typedef struct s_client		t_client;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;

/*
** Structures
*/

struct				s_o_champ
{
	t_u8			filename[MAX_O_SIZ];
	t_u8			code[MAX_O_SIZ];
};

struct				s_server
{
	int				master_socket;
	int				new_socket;
	socklen_t		addrlen;
	int				activity;
	int				client_socket[MAX_PLAYERS + 1];
	t_o_champ		champ[MAX_PLAYERS + 1];
	int				sd;
	int				maxsd;
	int				opt;
	int				n;
	t_u8			buffer[O_BUFFSIZE];
	fd_set			readfds;
};

struct				s_client
{
	t_o_champ		champ[MAX_PLAYERS + 1];
	int				sockfd;
	t_sockaddr_in	serv_addr;
	t_u8			buffer[O_BUFFSIZE];
};

void				ft_client_1(t_client client);
void				ft_client_2(t_client client);
void				ft_create_file(t_client client, int i);
void				ft_launch_vm(t_client client);
void				ft_game_start_cli(t_client client);
char				*ft_comp_champ(char *filename);
void				game_start_serv(t_server *serv, t_sockaddr_in *address);
void				ft_init_serv(t_server *serv, t_sockaddr_in *addr, int *i);
void				ft_get_champ_filename(t_server *serv, int i);
#endif
