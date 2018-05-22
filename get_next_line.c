/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/22 20:21:10 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> //
#include <fcntl.h> //
t_fd	*new_fd(int fd, char *reminder);
int		read_from_buffer(t_list *list, int fd, char **line, char *buff);
t_fd	*get_fd(t_list *list, int fd);

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
	if ((fd_data = get_fd(list, fd)))
		*line = ft_strappend(*line, fd_data->buff);
	res = read_from_buffer(list, fd, line, buff);
	return (res);
}

int		read_from_buffer(t_list *list, int fd, char **line, char *buff)
{
	char	*tmp;
	char	*reminder;

	tmp = NULL;
	reminder = NULL;
	while (!(reminder = ft_strchr(tmp, '\n')))
	{
		read(fd, buff, BUFF_SIZE);
		tmp = ft_strappend(tmp, buff);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	*line = ft_strndup(tmp, reminder - tmp);
	if (*(reminder + 1) == '\0')
	{
		if (read(fd, buff, BUFF_SIZE))
			reminder = ft_strdup(buff);
		else
			return (0);
	}
	ft_lstadd(&list, ft_lstnew(new_fd(fd, reminder), sizeof(t_fd)));
	return (1);
}

t_fd	*get_fd(t_list *list, int fd)
{
	t_list	*ptr;
	t_list	*prev;
	t_fd	*data;

	ptr = list;
	prev = list;
	data = NULL;
	while (ptr != NULL)
	{
		data = ptr->content;
		if (data->fd == fd)
			break;
		ptr = ptr->next;
	}
	if (ptr)
	{
		while (prev->next != ptr)
			prev = prev->next;
		prev->next = ptr->next;
		ft_lstdelone(&ptr, ft_del);
		return (data);
	}
	return (NULL);
}

t_fd	*new_fd(int fd, char *reminder)
{
	t_fd	*new;

	new->fd = fd;
	new->buff = ft_strdup(reminder);
	return (new);
}
