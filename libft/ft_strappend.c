/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:50:36 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/21 22:19:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *dst, char *append)
{
	size_t	d_len;
	size_t	a_len;
	char	*new;

	d_len = ft_strlen(dst);
	a_len = ft_strlen(append);
	new = ft_strnew(d_len + a_len);
	new = ft_strcpy(new, dst);
	new = ft_strncat(new, append, a_len);
	new[d_len + a_len] = '\0';
	//ft_strdel(&dst);
	dst = new;
	new = NULL;
	return (dst);
}
