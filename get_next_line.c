/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/21 03:57:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> //
#include <fcntl.h> //

void	push_fd(t_fd **list, const int fd);
t_fd	*find_fd(t_fd *list, const int fd);

int		main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		test;

	test = 1;
	fd = open(av[1], O_RDONLY);
	int fd2 = open(av[2], O_RDONLY);
	int i = 0;
	//ft_putnbr(get_next_line(fd, &line));
	while (test)
	{
		if (i % 2 == 0)
			test = get_next_line(fd, &line);
		else
		{
			test = get_next_line(fd2, &line);
		}
		//ft_putnbr(test);
		//ft_putstr(line);
		//ft_putchar('\n');
		i++;
	}
	//ft_putstr(line);
	//ft_print_memory(line, 30);
	close(fd);
	close(fd2);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_fd		*list;
	t_fd			*ptr;
	char			buff[BUFF_SIZE + 1];

	bzero(buff, BUFF_SIZE);
	if (list)
	{
		if ((ptr = find_fd(list, fd)))
		{
			int lol = read_from_fd_buffer(ptr, buff, line);
			//ft_putstr(*line);
			//return (read_from_fd_buffer(ptr, buff, line));
			ft_putstr(*line);
			return (lol);
		}
	}
	else
	{
		push_fd(&list, fd);
		return (get_next_line(fd, line));
	}
}

#include <stdlib.h>

void	push_fd(t_fd **list, const int fd)
{
	t_fd	*ptr;
	t_fd	*new;

	ptr = *list;
	new = (t_fd*)malloc(sizeof(*new));
	new->fd = fd;
	new->buff = NULL;
	new->size = 0;
	new->next = NULL;
	if (ptr)
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	else
		*list = new;
	ptr = NULL;
}

t_fd	*find_fd(t_fd *list, const int fd)
{
	t_fd *ptr;

	ptr = list;
	while (ptr != NULL && ptr->fd != fd)
		ptr = ptr->next;
	return (ptr);
}

int		read_from_fd_buffer(t_fd *ptr, char *buff, char **line)
{
	int		size;
	int		i;

	size = 1;
	i = 0;
	while (!has_line(ptr->buff) && size > 0)
	{
		ft_bzero(buff, BUFF_SIZE + 1);
		size = read(ptr->fd, buff, BUFF_SIZE);
		//ft_putstr(buff);
		if (ptr->buff)
		{
			ptr->buff = ft_strjoin(ptr->buff, buff);
		}
		else
			ptr->buff = ft_strdup(buff);
	}
	ptr->size = trim_buff(&(ptr->buff), line);
	//ft_putnbr(ptr->size);
	//ft_putchar(' ');
	//ft_putstr(ptr->buff);
	//ft_putstr(*line);
	return (size > 0 || ptr->size > 0 ? 1 : 0);
}

int		has_line(char *buff)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (buff == NULL)
		return (0);
	while (buff[i])
	{
		if (flag == 0 &&buff[i] != '\n')
			flag = 1;
		if (buff[i] == '\n' && flag == 1)
			return (1);
		i++;
	}
	return (0);
}

int		trim_buff(char **buff, char **line)
{
	int i;
	int j;
	char *ptr;

	i = 0;
	j = 0;
	while ((*buff)[j] == '\n')
		j++;
	while ((*buff)[j + i] && (*buff)[j + i] != '\n')
		i++;
	*line = ft_strndup(*buff + j, i);
	ptr = ft_strdup(*buff + (j + i));
	*buff = ptr;
	ft_strdel(&ptr);
	return (ft_strlen(*buff));
}
