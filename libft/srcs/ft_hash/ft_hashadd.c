/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:59:17 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/03 20:19:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	TODO: Check if key already exists in list (ERROR case)
*/

int		ft_hashadd(t_htable *table, t_hash *entry)
{
	int hash;

	hash = ft_hash(table, entry->key);
	if (table && entry)
	{
		ft_hashpush(table, entry);
		return (1);
	}
	return (-1);
}
