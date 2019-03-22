/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:42:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/22 20:43:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

typedef struct s_gnl
{
	char *remains;
	size_t remains_len;
	char buff[BUFF_SIZE + 1];
	int newline_index;
	int read_status;
	int has_newline;
} t_gnl;

static void	get_remains_for_file(const int fd, t_dict **list, char **remains)
{
	*remains = (char*)ft_dictget(list, fd);
}

static int	read_file_until_eol(const int fd, t_gnl *scanner)
{
	while (scanner->read_status)
	{
		if ((scanner->newline_index = ft_strchri(scanner->remains, '\n')) >= 0)
			break;;
		if ((scanner->read_status = (int)read(fd, scanner->buff, BUFF_SIZE)) < 0)
			return (-1);
		scanner->buff[scanner->read_status] = '\0';
		if (!(scanner->remains = ft_strappend(scanner->remains, scanner->buff)))
			return (-1);
	}
	if (scanner->newline_index >= 0)
		scanner->has_newline = 1;
	else
		scanner->has_newline = 0;
	scanner->remains_len = ft_strlen(scanner->remains);
	return (0);
}
static int	add_file_remains_to_dict(int fd, t_gnl *scanner, t_dict **list)
{
	char *file_remains;
	size_t remains_len;

	file_remains = scanner->remains + (scanner->newline_index + 1);
	remains_len = ft_strlen(file_remains) + 1;
	if (ft_dictadd(list, fd, file_remains, remains_len) < 0)
		return (-1);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_dict	*list;
	t_gnl			scanner;

	scanner.read_status = 1;
	if (fd < 0 || !line)
		return (-1);
	get_remains_for_file(fd, &list, &scanner.remains);
	if (read_file_until_eol(fd, &scanner) < 0)
		return (-1);
	if (scanner.remains_len > 0)
	{
		if (scanner.has_newline)
			*line = ft_strsub(scanner.remains, 0, scanner.newline_index);
		else
			*line = ft_strsub(scanner.remains, 0, ft_strlen(scanner.remains));
		if (!*line)
			return (-1);
	}
	/* if there's something left to store from rest */
	if (scanner.has_newline)
	{
		if (add_file_remains_to_dict(fd, &scanner, &list) < 0)
			return (-1);
	}
	ft_strdel(&scanner.remains);
	if (scanner.remains_len > 0)
		return (1);
	else
		return (scanner.read_status);
}
