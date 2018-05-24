/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/25 00:51:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h> //
#include <fcntl.h> //
#include <stdlib.h>
t_fd	*new_fd(int fd, char *reminder);
char	*get_fd(t_hash **list, int fd);
void	save_remain(t_hash **list, char *remainder, int fd);
char		*trim_nl(char *src);

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
			//ft_putchar('\n');
			ft_strdel(&line);
		}
		if (fd2)
		{
			size = get_next_line(fd2, &line);
			if (line)
			{
				ft_putstr_npr(line);
				//ft_putchar('\n');
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
	static t_hash	*list;
	char			*reminder;
	char			buff[BUFF_SIZE + 1];
	int				i;
	int				ret;

	i = 0;
	ret = 1;
	reminder = get_fd(&list, fd);
	if (reminder)
	{
		reminder = trim_nl(reminder);
	}
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
	if (i == ft_strlen(reminder) || i < 0)
		*line = ft_strdup(reminder);
	else
	{
		*line = ft_strsub(reminder, 0, i);
		save_remain(&list, ft_strdup(reminder + i), fd);
	}
	return (ret > 0 ? 1 : 0);
}

void		save_remain(t_hash **list, char *remainder, int fd)
{
	t_hash	*ptr;

	ptr = ft_hashnew(fd, remainder, sizeof(*remainder) * ft_strlen(remainder)); // THANKS TO THIS !
	ft_hashpush(list, ptr);
	//ft_putstr_npr(((char*)(*list)->data)); // IT WORKS !!!
}

char		*get_fd(t_hash **list, int fd)
{
	t_hash	*ptr;
	char	*tmp;

	if ((ptr = ft_hashpopkey(list, fd)))
	{
		if (!(tmp = ft_strdup((char*)ptr->data)))
			return (NULL);
		ft_hashdel(&ptr);
		return (tmp);
	}
	return (NULL);
}

char		*trim_nl(char *src)
{
	int i;
	int j;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	while (src[i] == '\n')
		i++;
	while (src[i + j] && src[i + j] != '\n')
		j++;
	if (i != j)
	{
		res = ft_strsub(src, i, j);
		ft_strdel(&src);
	}
	return (res);
}
