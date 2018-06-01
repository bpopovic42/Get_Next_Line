/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 18:25:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/01 17:57:27 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	read_from_fds(int *fd, int ac, char *line);
int		*get_fd_tab(int ac, char **av);

int		main(int ac, char **av)
{
	int		*fd;
	char	*line;
	int		size;
	int		i;

	line = NULL;
	fd = NULL;
	size = 1;
	i = 0;
	if (ac > 1)
	{
		if (!(fd = get_fd_tab(ac, av)))
			return (1);
	}
	if (fd)
		read_from_fds(fd, ac, line);
	else
	{
		while (size)
		{
			size = get_next_line(0, &line);
			ft_putstr_npr(line);
			ft_strdel(&line);
		}
	}
	if (fd)
		free(fd);
	if (line)
		ft_strdel(&line);
}

void	read_from_fds(int *fd, int ac, char *line)
{
	int flag;
	int i;

	flag = 1;
	i = 0;
	while (flag)
	{
		flag = 0;
		while (i < ac)
		{
			if (fd[i] > -1)
			{
				if (get_next_line(fd[i], &line) == 0)
				{
					close(fd[i]);
					fd[i] = -1;
				}
				else
					flag = 1;
				ft_putstr(line);
				//ft_putchar(line[0]);
				//ft_print_memory(line, 8);
				ft_strdel(&line);
			}
			i++;
		}
		i = 0;
	}
}

int		*get_fd_tab(int ac, char **av)
{
	int i;
	int *fd;

	i = 0;
	if (!(fd = (int*)malloc(sizeof(*fd) * (unsigned long)ac)))
		return (NULL);
	while (i < ac)
	{
		fd[i] = open(av[i + 1], O_RDONLY);
		i++;
	}
	return(fd);
}
