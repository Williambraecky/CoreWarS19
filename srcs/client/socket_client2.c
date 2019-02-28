/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_client2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouvroy <nrouvroy@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:27:52 by nrouvroy          #+#    #+#             */
/*   Updated: 2019/02/28 15:23:11 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "online.h"

void	ft_create_file(t_client client, int i)
{
	int	fd;
	int	to_print;

	printf("filename : %s\n", (char*)client.champ[i].filename);
	if ((fd = open((char*)client.champ[i].filename,
					O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
		ft_o_exit("\nERROR : writing champ\n");
	to_print = n_bytes_to_uint(client.champ[i].code + 8 +
			PROG_NAME_LENGTH, 4) + 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	write(fd, client.champ[i].code, to_print);
	close(fd);
}

void	ft_launch_vm(t_client client)
{
	char	cmd[O_BUFFSIZE];
	int		i;

	i = 0;
	ft_strcat(cmd, "./corewar -visu ");
	while (++i <= MAX_PLAYERS)
	{
		ft_strcat(cmd, (char*)client.champ[i].filename);
		ft_strcat(cmd, " ");
	}
	system(cmd);
	exit(0);
}

void	ft_game_start_cli(t_client client)
{
	int		i;

	i = 0;
	while (++i <= MAX_PLAYERS)
	{
		read(client.sockfd, client.buffer, O_BUFFSIZE);
		ft_memcpy(client.champ[i].filename, client.buffer, O_BUFFSIZE);
		usleep(25000);
		read(client.sockfd, client.buffer, O_BUFFSIZE);
		ft_memcpy(client.champ[i].code, client.buffer, O_BUFFSIZE);
		usleep(25000);
	}
	i = 0;
	while (++i <= MAX_PLAYERS)
		ft_create_file(client, i);
	ft_launch_vm(client);
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
