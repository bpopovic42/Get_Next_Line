/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:12:14 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 21:13:59 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memchri(void *s, int c, size_t size)
{
	size_t i;

	i = 0;
	while (i < size && ((char*)s)[i] != c)
		i++;
	if (i == size)
		return (-1);
	else
		return (i);
}
