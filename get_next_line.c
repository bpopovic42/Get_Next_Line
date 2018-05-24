/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/24 21:21:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> //
#include <fcntl.h> //
#include <stdlib.h>
t_fd	*new_fd(int fd, char *reminder);
char	*get_fd(t_list **list, int fd);
void	save_remain(t_list **list, char *remainder, int fd);

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
			ft_strdel(&line);
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
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list;
	char			*reminder;
	char			buff[BUFF_SIZE + 1];
	int				i;
	int				ret;

	i = 0;
	ret = 1;
	reminder = get_fd(&list, fd);
	while ((i = ft_strchrin(reminder, '\n')) < 0)
	{
		ret = read(fd, buff, BUFF_SIZE);
		buff[ret] = '\0';
		reminder = ft_strappend(reminder, buff);
		if (ret == 0)
		{
			*line = ft_strdup(reminder);
			ft_strdel(&reminder);
			return (ret);
		}
	}
	ft_putchar('X');
	ft_putstr_npr(reminder);
	ft_putendl("X");
	if (i == ft_strlen(reminder) || i < 0)
		*line = ft_strdup(reminder);
	else
	{
		*line = ft_strsub(reminder, 0, i);
		save_remain(&list, ft_strdup(reminder + i + 1), fd);
	}
	return (ret > 0 ? 1 : 0);
}

void		save_remain(t_list **list, char *remainder, int fd)
{
	t_list	*ptr;
	t_fd	*new;

	ptr = *list;
	new = NULL;
	if (ptr)
	{
	while (ptr->next != NULL && ((t_fd*)ptr->content)->fd != fd)
		ptr = ptr->next;
	if (((t_fd*)ptr->content)->fd == fd)
	{
		if (((t_fd*)ptr->content)->buff)
			ft_strdel(&((t_fd*)ptr->content)->buff);
		((t_fd*)ptr->content)->buff = remainder;
	}
	else if (ptr->next == NULL)
	{
		new = (t_fd*)malloc(sizeof(t_fd));
		new->fd = fd;
		new->buff = remainder;
		ptr->next = ft_lstnew(new, sizeof(new));
	}
	}
	else
	{
		new = (t_fd*)malloc(sizeof(*new));
		new->fd = fd;
		new->buff = ft_strdup(remainder);
		ft_strdel(&remainder);
		*list = ft_lstnew(new, sizeof(*new));
	}
}

char		*get_fd(t_list **list, int fd)
{
	t_list	*ptr;
	char	*tmp;

	ptr = *list;
	tmp = NULL;
	while (ptr)
	{
		if (((t_fd*)ptr->content)->fd == fd)
		{
			tmp = ft_strdup(((t_fd*)ptr->content)->buff);
			ft_strdel(&((t_fd*)ptr->content)->buff);
			free(ptr->content);
			return (tmp);
		}
		ptr = ptr->next;
	}
	return (NULL);
}
