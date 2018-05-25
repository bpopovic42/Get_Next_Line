/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 18:25:52 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/25 18:31:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h> //
#include <fcntl.h> //
#include <stdlib.h>

int		main(int ac, char **av)
{
	int		*fd;
	char	*line;
	int		size;
	int		i;
	int		std;
	int		flag;

	line = NULL;
	size = 1;
	i = 0;
	fd = NULL;
	flag = 1;
	if (ac > 1)
	{
		fd = (int*)malloc(sizeof(*fd) * (unsigned long)ac - 1);
		while (i < ac)
		{
			fd[i] = open(av[i + 1], O_RDONLY);
			i++;
		}
	}
	else
		std = 0;
	i = 0;
	if (fd)
	{
		while (flag)
		{
			flag = 0;
			while (i < ac)
			{
				if (fd[i] > -1)
				{
					if (!(size = get_next_line(fd[i], &line)))
					{
						close(fd[i]);
						fd[i] = -1;
					}
					else
					{
						flag = 1;
						ft_putstr_npr(line);
						ft_strdel(&line);
					}
				}
				i++;
			}
			i = 0;
		}
	}
	else
	{
		while (size)
		{
			size = get_next_line(0, &line);
			ft_putstr_npr(line);
			ft_strdel(&line);
		}
	}
	if (line)
		ft_strdel(&line);
}
