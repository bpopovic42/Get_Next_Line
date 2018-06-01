/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 20:59:10 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 21:07:08 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcat(void *dst, const void *append, size_t n)
{
	int		d_len;
	size_t	i;

	d_len = ft_strlen((char*)dst);
	i = 0;
	while (i < n)
	{
		((char*)dst)[d_len + i] = ((char*)append)[i];
		i++;
	}
	return (dst);
}
