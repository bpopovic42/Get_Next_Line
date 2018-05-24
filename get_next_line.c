/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/24 15:09:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> //
#include <fcntl.h> //
#include <stdlib.h>
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
		if (line)
		{
			ft_putstr_npr(line);
			ft_putchar('\n');
		}
		if (fd2)
		{
			size = get_next_line(fd2, &line);
			if (line)
			{
				ft_putstr_npr(line);
				ft_putchar('\n');
			}
		}
		i++;
	}
	if (line)
		ft_strdel(&line);
	close(fd1);
	if (ac == 3)
		close(fd2);
	while (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_fd			*fd_data;
	char			*reminder;
	int				i;

	fd_data = NULL;
	reminder = NULL;
	i = 0;
	if (*line)
		ft_strdel(line);
	if ((fd_data = get_fd(&list, fd)) != NULL)
	{
		while (fd_data->buff[i] && fd_data->buff[i] != '\n')
		{
			i++;
		}
		if (fd_data->buff[i])
		{
			*line = ft_strnappend(*line, fd_data->buff, i);
			reminder = ft_strappend(reminder, fd_data->buff + i);
		}
		else
		{
			*line = ft_strappend(*line, fd_data->buff);
		}
	}
	if (fd_data)
	{
		ft_strdel(&fd_data->buff);
		fd_data->fd = 0;
		free(fd_data);
		fd_data = NULL;
	}
	if (!read_from_buffer(&list, fd, line, reminder))
	{
		t_list *fuck = list;
		while (fuck)
		{
			if (((t_fd*)fuck->content)->fd == fd)
			{
				if ((((t_fd*)fuck->content)->buff) != NULL)
				{
					ft_strdel(&((t_fd*)fuck->content)->buff);
				}
				ft_lstdelone(&fuck, &ft_del);
				break;
			}
			fuck = fuck->next;
		}
		fuck = NULL;
		if (reminder)
			ft_strdel(&reminder);
		return (0);
	}
	if (reminder)
		ft_strdel(&reminder);
	return (1);
}

int		read_from_buffer(t_list **list, int fd, char **line, char *reminder)
{
	char	*tmp;
	char	buff[BUFF_SIZE + 1];

	tmp = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	if (!reminder)
	{
		while (!(reminder = ft_strchr(tmp, '\n')))
		{
			if (!read(fd, buff, BUFF_SIZE))
				return (0);
			tmp = ft_strappend(tmp, buff);
			ft_bzero(buff, BUFF_SIZE + 1);
		}
		*line = ft_strnappend(*line, tmp, reminder - tmp);
		reminder = ft_strdup(tmp + (reminder - tmp));
		ft_strdel(&tmp);
	}
	if (*(reminder) == '\0' || *(reminder) == '\n')
	{
		if ((reminder = is_eof(fd, buff, reminder)) == NULL)
		{
			if (reminder != NULL)
				ft_strdel(&reminder);
			t_list *test = *list;
			while (test)
			{
				if (((t_fd*)test->content)->fd == fd)
				{
					ft_lstdelone(&test, &ft_del);
					break;
				}
				test = test->next;
			}
			return (0);
		}
	}
	t_fd *new = NULL;
	if (reminder)
	{
		new = new_fd(fd, reminder);
		ft_lstadd(list, ft_lstnew(new, sizeof(t_fd)));
		ft_strdel(&new->buff);
		free(new);
	}
	ft_strdel(&reminder);
	return (1);
}

char		*is_eof(int fd, char *buff, char *reminder)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (reminder && *(reminder) == '\n')
	{
		while (reminder[i] && reminder[i] == '\n')
		{
			i++;
		}
		if (reminder[i])
		{
			tmp = reminder;
			reminder = ft_strdup(tmp + i);
			ft_strdel(&tmp);
			return (reminder);
		}
	}
	i = 0;
	if (reminder != NULL)
		ft_strdel(&reminder);
	while (read(fd, buff, BUFF_SIZE))
	{
		while (buff[i] && buff[i] == '\n')
		{
			i++;
		}
		if (buff[i])
		{
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

	/*t_list *lol = *list;
	t_fd	*heh = NULL;
	while (lol != NULL)
	{
		heh = lol->content;
		ft_putchar('X');
		ft_putstr(heh->buff);
		ft_putnbr(heh->fd);
		ft_putendl("X");
		lol = lol->next;
	}*/

	while (ptr != NULL)
	{
		data = ptr->content;
		if (data->fd == fd)
		{
			break;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr)
	{
		new = new_fd(data->fd, data->buff);
		ft_strdel(&data->buff);
		/*char *fuck = ((t_fd*)ptr->content)->buff;
		if (fuck)
			free(&fuck);*/
		data->fd = 0;
		free(data);
		data = NULL;
		if (prev != ptr)
			prev->next = ptr->next;
		else
		{
			prev = ptr->next;
			*list = prev;
		}
		//ft_lstdelone(&ptr, &ft_del);// ISSUE
		ptr->next = NULL;
		free(ptr);
		ptr = NULL;
		prev = NULL;
	}

	/*lol = *list;
	heh = NULL;
	while (lol != NULL)
	{
		heh = lol->content;
		ft_putchar('W');
		ft_putstr(heh->buff);
		ft_putnbr(heh->fd);
		ft_putendl("W");
		lol = lol->next;
	}*/

	return (new);
}


t_fd	*new_fd(int fd, char *reminder)
{
	t_fd	*new;

	new = (t_fd*)malloc(sizeof(*new));
	new->fd = fd;
	new->buff = ft_strdup(reminder);
	return (new);
}
