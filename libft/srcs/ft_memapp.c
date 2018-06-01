/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:50:36 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 21:57:50 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memapp(void *d, const void *ap, size_t dl, size_t al)
{
	void	*new;

	if (!(new = ft_memalloc(sizeof(char) * (dl + al))))
		return (NULL);
	if (d)
	{
		new = ft_memcpy(new, d, dl);
		if (ap)
			new = ft_memcat(new, ap, al);
		ft_memdel(&d);
	}
	else if (ap)
		new = ft_memcpy(new, ap, al);
	((char*)new)[dl + al] = '\0';
	return (new);
}
