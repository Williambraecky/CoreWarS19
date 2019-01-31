/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 15:15:20 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/01/31 03:19:19 by nrouvroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "online.h"

char 	*ft_comp_champ(char *filename)
{
	int		l;
	char	cmd[103];

	if ((l = ft_strlen(filename)) >= 98)
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

int main(int argc, char **argv)
{
	int			n;
	t_client	client;

	if (argc != 2)
		ft_o_exit("Usage : ./online champion.[s|cor]\n");
	ft_strcpy(client.filename, ft_comp_champ(argv[1]));
	printf("filename : %s\n",client.filename);
	ft_memset(client.buffer, '0', sizeof(client.buffer));
	if ((client.sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_o_exit("\nERROR : could not create socket\n");
	client.serv_addr.sin_family = AF_INET;
	client.serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "10.2.2.4", &client.serv_addr.sin_addr) <= 0)
		ft_o_exit("\nERROR : invalid ip\n");
	ft_printf("ready to connect\n");
	if (connect(client.sockfd, (struct sockaddr*)&client.serv_addr, sizeof(client.serv_addr)) < 0)
		ft_o_exit("\nERROR : connect failed\n");
	ft_printf("connected\n");
	usleep(500000);
	if ((n = read(client.sockfd, client.buffer, sizeof(client.buffer) - 1)) > 0)
	{
		client.buffer[n] = 0;
		if (ft_printf("msg in buffer from server : %s\n", client.buffer) < 0)
			ft_printf("\nERROR : printf or read error\n");
		if (ft_strchr(client.buffer, '['))
		{
			client.playerID = ft_atoi(ft_strchr(client.buffer, '[') + 1);
			printf("playerID : %d\n", client.playerID);
		}
		else if (ft_strstr(client.buffer, "Sorry but the"))
			ft_o_exit(client.buffer);
		else
			ft_o_exit("\nERROR : wrong answer from server\n");
	}
	if (n < 0)
		ft_printf("\nERROR : Read error\n");
	sleep(1);
	ft_strcpy(client.buffer, client.filename);
	send(client.sockfd, client.buffer, ft_strlen(client.filename), 0);
	usleep(50000);
	ft_strcpy(client.buffer, "START_CODE_CHAMPION\0");
	send(client.sockfd, client.buffer, O_BUFFSIZE, 0);
	usleep(50000);
	//TODO while (n = read(fd from filename));
	ft_strcpy(client.buffer, "CHAMPION_DUMMY_CODE\0");
	send(client.sockfd, client.buffer, O_BUFFSIZE, 0);
	usleep(50000);
	ft_strcpy(client.buffer, "END_CODE_CHAMPION\0");
	send(client.sockfd, client.buffer, O_BUFFSIZE, 0);
	while (1)
		;
	/*
	while (1)
	{
		ft_strcpy(client.buffer, argv[1]);
		send(client.sockfd, client.buffer, ft_strlen(client.buffer), 0);
		ft_printf("message sent\n");
		usleep(500000);
	}*/
	return (0);
}
