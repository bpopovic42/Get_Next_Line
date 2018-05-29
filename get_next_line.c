/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 22:23:04 by bopopovi         ###   ########.fr       */
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
	size_t			total;

	ret = 1;
	total = 0;
	remain = NULL;
	if (fd < 0 || !(line))
		return (-1);
	total = get_fd(&list, fd, &remain);
	while ((i = ft_memchri(remain, '\n', total)) < 0 && ret)
	{
		if ((ret = (int)read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		buff[ret] = '\0';
		remain = ft_memapp(remain, buff, total, ret);
		total += ret;
	}
	ft_putstrn(remain, total);
	*line = (i >= 0) ? ft_strsub(remain, 0, (size_t)i) : ft_strndup(remain, total);
	if (i >= 0)
		save_remain(&list, ft_memdup(remain + i + 1, total - i), fd, total - i);
	ret = (remain[0]) ? 1 : ret;
	ft_strdel(&remain);
	return (ret);
}

void		save_remain(t_hash **list, char *remain, int fd, int size)
{
	t_hash	*ptr;

	ptr = ft_hashnew(fd, remain, (sizeof(*remain) * size) + 1);
	ft_strdel(&remain);
	ft_hashpush(list, ptr);
}

size_t		get_fd(t_hash **list, int fd, char **remain)
{
	t_hash	*ptr;
	size_t	data_size;

	if ((ptr = ft_hashpopkey(list, fd)))
	{
		if (!(*remain = ft_strdup((char*)ptr->data)))
			return (0);
		data_size = ptr->data_size;
		ft_hashdel(&ptr);
		return (data_size);
	}
	return (0);
}
