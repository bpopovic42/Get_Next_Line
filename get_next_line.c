/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/23 17:32:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> //
#include <fcntl.h> //
t_fd	*new_fd(int fd, char *reminder);
int		read_from_buffer(t_list **list, int fd, char **line, char *buff);
t_fd	*get_fd(t_list **list, int fd);
char	*is_eof(int fd, char *buff, char *reminder);

int		main(int ac, char **av)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		size;
	int		i;

	fd1 = 0;
	fd2 = 0;
	line = NULL;
	size = 1;
	i = 0;
	if (ac > 1)
	{
		fd1 = open(av[1], O_RDONLY);
		if (ac == 3)
			fd2 = open(av[2], O_RDONLY);
	}
	while (size)
	{
		size = get_next_line(fd1, &line);
		ft_putstr_npr(line);
		ft_putchar('\n');
		if (fd2)
		{
			size = get_next_line(fd2, &line);
			ft_putstr_npr(line);
			ft_putchar('\n');
		}

		i++;
	}
	close(fd1);
	if (ac == 3)
		close(fd2);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list;
	char			buff[BUFF_SIZE + 1];
	int				res;
	t_fd			*fd_data;

	ft_bzero(buff, BUFF_SIZE + 1);
	fd_data = NULL;
	if (*line)
		ft_strdel(line);
	if ((fd_data = get_fd(&list, fd)) != NULL)
	{
		*line = ft_strappend(*line, fd_data->buff);
	}
	res = read_from_buffer(&list, fd, line, buff);
	return (res);
}

int		read_from_buffer(t_list **list, int fd, char **line, char *buff)
{
	char	*tmp;
	char	*reminder;
	char	*lol = NULL;

	tmp = NULL;
	reminder = NULL;
	while (!(reminder = ft_strchr(tmp, '\n')))
	{
		read(fd, buff, BUFF_SIZE);
		tmp = ft_strappend(tmp, buff);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	lol = ft_strndup(tmp, reminder - tmp);
	*line = ft_strappend(*line, lol);
	ft_strdel(&lol);
	reminder = ft_strdup(tmp + (reminder - tmp));
	ft_strdel(&tmp);
	if (*(reminder + 1) == '\0' || *(reminder + 1) == '\n')
	{
		if ((reminder = is_eof(fd, buff, reminder)) == NULL)
			return (0);
	}
	ft_lstadd(list, ft_lstnew(new_fd(fd, reminder), sizeof(t_fd)));
	return (1);
}

char		*is_eof(int fd, char *buff, char *reminder)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (reminder && *(reminder + 1) == '\n')
	{
		while (reminder[i] && reminder[i] == '\n')
			i++;
		if (reminder[i])
		{
			tmp = reminder;
			reminder = ft_strdup(tmp + i);
			ft_strdel(&tmp);
			return (reminder);
		}
	}
	i = 0;
	while (read(fd, buff, BUFF_SIZE))
	{
		while (buff[i] && buff[i] == '\n')
			i++;
		if (buff[i])
		{
			if (reminder != NULL)
				ft_strdel(&reminder);
			return (ft_strdup(buff + i));
		}
		ft_bzero(buff, BUFF_SIZE + 1);
		i = 0;
	}
	return (NULL);
}

t_fd	*get_fd(t_list **list, int fd)
{
	t_list	*ptr;
	t_list	*prev;
	t_fd	*data;
	t_fd	*new;

	ptr = *list;
	prev = *list;
	data = NULL;
	new = NULL;
	while (ptr != NULL)
	{
		data = ptr->content;
		if (data->fd == fd)
			break;
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr)
	{
		new = new_fd(data->fd, data->buff);
		data = NULL;
		prev->next = ptr->next;
		ft_lstdelone(&ptr, ft_del);
	}
	return (new);
}

#include <stdlib.h>

t_fd	*new_fd(int fd, char *reminder)
{
	t_fd	*new;

	new = (t_fd*)malloc(sizeof(*new));
	new->fd = fd;
	new->buff = ft_strdup(reminder);
	return (new);
}
