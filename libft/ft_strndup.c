/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:26:49 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/21 02:42:13 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char *res;

	if (!(res = (char*)malloc(sizeof(*res) * n + 1)))
		return (NULL);
	res = ft_strncpy(res, s1, n + 1);
	res[n] = '\0';
	return (res);
}
