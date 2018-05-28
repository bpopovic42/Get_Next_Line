/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/28 17:10:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

int			get_next_line(const int fd, char **line)
{
	static t_hash	*list;
	char			*remain;
	char			buff[BUFF_SIZE + 1];
	int				i;
	int				ret;

	ret = 1;
	if (fd < 0 || !(line))
		return (-1);
	remain = get_fd(&list, fd);
	while ((i = ft_strchri(remain, '\n')) < 0 && ret)
	{
		if ((ret = (int)read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		buff[ret] = '\0';
		remain = ft_strappend(remain, buff);
	}
	*line = (i >= 0) ? ft_strsub(remain, 0, (size_t)i) : ft_strdup(remain);
	if (i >= 0)
		save_remain(&list, ft_strdup(remain + i + 1), fd);
	ret = (remain[0]) ? 1 : ret;
	ft_strdel(&remain);
	return (ret);
}

void		save_remain(t_hash **list, char *remain, int fd)
{
	t_hash	*ptr;

	ptr = ft_hashnew(fd, remain, (sizeof(*remain) * ft_strlen(remain)) + 1);
	ft_strdel(&remain);
	ft_hashpush(list, ptr);
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
