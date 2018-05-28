/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:45:59 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/28 16:55:41 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1024

# include "libft.h"

typedef struct		s_fd
{
	int				fd;
	char			*buff;
}					t_fd;

int					get_next_line(const int fd, char **line);
char				*get_fd(t_hash **list, int fd);
void				save_remain(t_hash **list, char *remain, int fd);

#endif
