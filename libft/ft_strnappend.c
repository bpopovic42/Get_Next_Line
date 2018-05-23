/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnappend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:50:36 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/23 18:48:52 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnappend(char *dst, char *append, size_t n)
{
	size_t	d_len;
	char	*new;

	d_len = dst ? ft_strlen(dst) : 0;
	new = ft_strnew(d_len + n);
	if (dst)
	{
		new = ft_strcpy(new, dst);
		if (append)
			new = ft_strncat(new, append, n);
		ft_strdel(&dst);
	}
	else if (append)
		new = ft_strncpy(new, append, n);
	new[d_len + n] = '\0';
	dst = new;
	new = NULL;
	return (dst);
}
