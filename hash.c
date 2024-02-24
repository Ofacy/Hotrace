/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:11:06 by lcottet           #+#    #+#             */
/*   Updated: 2024/02/24 18:26:41 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

t_hash	hash_str(char *str, size_t len)
{
	t_hash	a;
	t_hash	b;
	t_hash	hash;
	size_t	i;

	hash = 0;
	a = 63689;
	b = 378551;
	i = 0;
	while (i < len)
	{
		hash = hash * a + str[i];
		a *= b;
		i++;
	}
	return (hash);
}
