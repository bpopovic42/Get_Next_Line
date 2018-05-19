/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:45:59 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/19 15:09:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFF_SIZE 32

# include "./libft/libft.h"

typedef struct		s_fd
{
	int			size;
	int			fd;
	char		*buff;
	struct s_fd	*next;
}					t_fd;

int		get_next_line(const int fd, char **line);

#endif
