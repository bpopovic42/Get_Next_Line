/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:52:12 by bopopovi          #+#    #+#             */
/*   Updated: 2018/06/01 17:31:21 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_hashget(t_hash **list, int key)
{
	t_hash	*ptr;
	void	*data;

	data = NULL;
	if (*list)
	{
		ptr = ft_hashpop(list, key);
		if (!(data = ft_memdup(ptr->data, ptr->data_size)))
			return (NULL);
		ft_hashdel(&ptr);
		return (data);
	}
	return (NULL);
}
