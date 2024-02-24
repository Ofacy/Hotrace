/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:14:30 by lcottet           #+#    #+#             */
/*   Updated: 2024/02/24 15:50:52 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hashmap.h"

int	init_map(t_hashmap *map, size_t elemcount)
{
	size_t	i;

	map->size = elemcount;
	map->members = malloc(elemcount * sizeof(t_member));
	if (!map->members)
		return (1);
	i = 0;
	while (i < elemcount)
	{
		init_vector(&map->members[i].pairs, sizeof(char *));
		i++;
	}
	return (0);
}

int	add_element(t_hashmap *map, t_pair pair)
{
	return (add_vector(&map->members[pair.keyhash % map->size].pairs, &pair));
}

t_pair	*get_element_colision(t_member *mem, t_hash hash)
{
	size_t	i;
	t_pair	*pair;

	i = 0;
	while (i < mem->pairs.len)
	{
		pair = &((t_pair *)mem->pairs.ptr)[i];
		if (pair->keyhash == hash)
			return (pair);
		i++;
	}
	return (NULL);
}

t_pair	*get_element(t_hashmap *map, char *key, size_t keylen)
{
	size_t	mindex;
	t_hash	hash;

	hash = hash_str(key, keylen);
	mindex = hash % map->size;
	return (get_element_colision(&map->members[mindex], hash));
}

void	clear_map(t_hashmap *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->size)
	{
		j = 0;
		while (j < map->members[i].pairs.len)
		{
			free(((t_pair *)map->members[i].pairs.ptr)[j].key);
			free(((t_pair *)map->members[i].pairs.ptr)[j].value);
			j++;
		}
		i++;
		clear_vector(&map->members[i].pairs);
	}
}
