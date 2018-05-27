/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/28 00:53:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h> //

t_fd	*new_fd(int fd, char *reminder);
char	*get_fd(t_hash **list, int fd);
void	save_remain(t_hash **list, char *remainder, int fd);
int		is_line(char **str);

int		get_next_line(const int fd, char **line)
{
	static t_hash	*list;
	char			*reminder;
	char			buff[BUFF_SIZE + 1];
	int				i;
	int				ret;

	ret = 1;
	reminder = get_fd(&list, fd);
	while ((i = ft_strchrin(reminder, '\n')) < 0 && ret)
	{
		if ((ret = (int)read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		buff[ret] = '\0';
		reminder = ft_strappend(reminder, buff);
	}
	*line = (i >= 0) ? ft_strsub(reminder, 0, (size_t)i) : ft_strdup(reminder);
	if (i >= 0)
		save_remain(&list, ft_strdup(reminder + i + 1), fd);
	ret = (reminder[0]) ? 1 : ret;
	ft_strdel(&reminder);
	return (ret);
}

void		save_remain(t_hash **list, char *remainder, int fd)
{
	t_hash	*ptr;

	ptr = ft_hashnew(fd, remainder, (sizeof(*remainder) * ft_strlen(remainder)) + 1); // SOLVED
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
