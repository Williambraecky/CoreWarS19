/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:15:20 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/06 23:44:31 by nrouvroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "online.h"

void	ft_game_start_cli(t_client client)
{
	(void) client;
	//TODO finish this part
	//get players
	//laumch corewar
	//remove players?
}

char	*ft_comp_champ(char *filename)
{
	int		l;
	char	cmd[MAX_O_SIZ];

	if ((l = ft_strlen(filename)) >= O_BUFFSIZE)
		ft_o_exit("\nERROR : filename too long\n");
	if ((!ft_strstr(filename, ".s")) && (!ft_strstr(filename, ".cor")))
		ft_o_exit("\nERROR : not a valid chamion\n");
	ft_strcat(cmd, "./asm ");
	if (ft_strstr(filename, ".s"))
	{
		system(ft_strcat(cmd, filename));
		ft_strclr(cmd);
		ft_strncpy(cmd, filename, ft_strlen(filename) - 2);
		ft_strcat(cmd, ".cor");
	}
	else
		ft_strcpy(cmd, filename);
	return (ft_strcpy(cmd, cmd));
}

void	ft_init_client(t_client *client, char **argv)
{
	int	i;

	i = 0;
	while (++i < MAX_PLAYERS)
	{
		ft_memset(client->champ[i].filename, 0, MAX_O_SIZ);
		ft_memset(client->champ[i].code, 0, MAX_O_SIZ);
	}
	ft_memset(client->buffer, '0', sizeof(client->buffer));
	if ((client->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_o_exit("\nERROR : could not create socket\n");
	client->serv_addr.sin_family = AF_INET;
	client->serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, argv[1], &client->serv_addr.sin_addr) <= 0)
		ft_o_exit("\nERROR : invalid ip\n");
}

void	ft_init_o_champ(t_client *client, unsigned char *filename)
{
	int				i;
	int				fd;
	unsigned char	buff[1001];
	int				n;

	ft_memset(buff, 0, 1000);
	if ((fd = open((char *)filename, O_RDONLY)) == -1)
		ft_o_exit("\nERROR : Invalid file\n");
	i = 0;
	while ((n = read(fd, buff, 1000)) > 0)
	{
		if (i > MAX_O_SIZ)
			ft_o_exit("\nERROR : Champion too long\n");
		ft_memcpy(client->champ[0].code + i, buff, n);
		i += n;
	}
	if (n == -1)
		ft_o_exit("\nERROR : reading champion file\n");
	close(fd);
}

int		main(int argc, char **argv)
{
	t_client	client;

	if (argc != 3)
		ft_o_exit("Usage : ./online serverIP champion.[s|cor]\n");
	ft_memcpy(client.champ[0].filename,
			ft_comp_champ(argv[2]), ft_strlen(argv[2]) + 2);
	printf("filename : %s\n", client.champ[0].filename);
	if (access((char*)client.champ[0].filename, F_OK) == -1)
		ft_o_exit("\nERROR : file does not exist\n");
	printf("file does exist\n");
	ft_init_client(&client, argv);
	printf("client init OK\n");
	ft_init_o_champ(&client, client.champ[0].filename);
	ft_printf("ready to connect\n");
	if (connect(client.sockfd, (struct sockaddr*)&client.serv_addr,
				sizeof(client.serv_addr)) < 0)
		ft_o_exit("\nERROR : connect failed\n");
	ft_printf("connected\n");
	usleep(100000);
	ft_client_1(client);
	return (0);
}

void	ft_client_1(t_client client)
{
	int	n;

	if ((n = read(client.sockfd, (char*)client.buffer, O_BUFFSIZE)) > 0)
	{
		client.buffer[n] = 0;
		if (ft_printf("msg in buffer from server : %s\n", client.buffer) < 0)
			ft_printf("\nERROR : printf or read error\n");
		if (ft_strstr((char*)client.buffer, "ERROR"))
			ft_o_exit("\nERROR : server already full\n");
	}
	if (n < 0)
		ft_printf("\nERROR : Read error\n");
	usleep(50000);
	ft_memcpy(client.buffer, client.champ[0].filename, MAX_O_SIZ);
	send(client.sockfd, client.buffer, MAX_O_SIZ, 0);
	usleep(100000);
	ft_client_2(client);
}

void	ft_client_2(t_client client)
{
	int	n;

	ft_strcpy((char*)client.buffer, "START_CODE_CHAMPION\0");
	send(client.sockfd, client.buffer, O_BUFFSIZE, 0);
	usleep(50000);
	ft_memcpy(client.buffer, client.champ[0].code, MAX_O_SIZ);
	send(client.sockfd, client.buffer, O_BUFFSIZE, 0);
	usleep(100000);
	ft_strcpy((char*)client.buffer, "END_CODE_CHAMPION\0");
	send(client.sockfd, client.buffer, O_BUFFSIZE, 0);
	while ((n = read(client.sockfd, (char*)client.buffer, O_BUFFSIZE)) > 0)
	{
		client.buffer[n] = 0;
		ft_printf("%s", client.buffer);
		if (ft_strstr((char*)client.buffer, "Starting"))
			return(ft_game_start_cli(client));
	}
}
