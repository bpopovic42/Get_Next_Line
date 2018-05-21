/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/21 02:49:31 by bopopovi         ###   ########.fr       */
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

	test = 0;
	fd = open(av[1], O_RDONLY);
	//ft_putnbr(get_next_line(fd, &line));
	while ((test = get_next_line(fd, &line)))
	{
		//ft_putnbr(test);
		ft_putstr(line);
	}
	ft_putstr(line);
	//ft_print_memory(line, 30);
	close(fd);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_fd		*list;
	t_fd			*ptr;
	char			buff[BUFF_SIZE];

	bzero(buff, BUFF_SIZE);
	if (list)
	{
		if ((ptr = find_fd(list, fd)))
		{
			return (read_from_fd_buffer(ptr, buff, line));
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
	while (!has_line(ptr->buff))
	{
		ft_bzero(buff, BUFF_SIZE);
		size = read(ptr->fd, buff, BUFF_SIZE);
		if (ptr->buff)
			ft_strjoin(ptr->buff, buff);
		else
			ptr->buff = ft_strdup(buff);
	}
	ptr->size = trim_buff(&(ptr->buff), line);
	ft_putnbr(ptr->size);
	ft_putstr(ptr->buff);
	return (ptr->size);
}

int		has_line(char *buff)
{
	int i;

	i = 0;
	if (buff == NULL)
		return (0);
	while (buff[i])
	{
		if (buff[i] == '\n')
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
	ft_strdel(buff);
	*buff = ptr;
	ft_strdel(&ptr);
	return (ft_strlen(*buff));
}
