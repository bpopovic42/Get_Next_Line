/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashpopkey.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 23:52:12 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/29 21:27:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hash	*ft_hashpopkey(t_hash **list, int key)
{
	t_hash	*ptr;
	t_hash	*node;

	if (*list)
	{
		ptr = *list;
		node = ptr;
		while (ptr)
		{
			if (ptr->key == key)
			{
				if (ptr == *list)
					*list = (*list)->next;
				else
				{
					while (node->next != ptr)
						node = node->next;
					node->next = ptr->next;
				}
				return (ptr);
			}
			ptr = ptr->next;
		}
	}
	return (NULL);
}
