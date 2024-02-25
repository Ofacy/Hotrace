/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:11:06 by lcottet           #+#    #+#             */
/*   Updated: 2024/02/25 17:50:39 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

t_hash	hash_str(char *str, size_t *len)
{
	t_hash	a;
	t_hash	hash;
	size_t	i;

	hash = 0;
	a = 63689;
	i = 0;
	while (str[i])
	{
		hash = hash * a + str[i];
		a *= 378551;
		i++;
	}
	if (len)
		*len = i;
	return (hash);
}
