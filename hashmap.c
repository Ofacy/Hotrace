/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:14:30 by lcottet           #+#    #+#             */
/*   Updated: 2024/02/25 13:54:57 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hashmap.h"

int	add_element(t_hashmap *map, t_pair pair)
{
	size_t	mindex;

	mindex = pair.keyhash % HASHMAP_SIZE;
	if (map->members[mindex].pairs.element_size == 0)
		init_vector(&map->members[mindex].pairs, sizeof(t_pair));
	return (add_vector(&map->members[pair.keyhash % HASHMAP_SIZE].pairs,
			&pair));
}

t_pair	*get_element_colision(t_member *mem, t_hash hash, char *key)
{
	size_t	i;
	t_pair	*pair;

	i = 0;
	while (i < mem->pairs.len)
	{
		pair = &((t_pair *)mem->pairs.ptr)[i];
		if (pair->keyhash == hash && ft_strcmp(pair->key, key) == 0)
			return (pair);
		i++;
	}
	return (NULL);
}

t_pair	*get_element(t_hashmap *map, t_hash hash, char *key)
{
	size_t	mindex;

	mindex = hash % HASHMAP_SIZE;
	return (get_element_colision(&map->members[mindex], hash, key));
}

void	clear_map(t_hashmap *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		j = 0;
		while (j < map->members[i].pairs.len)
		{
			free(((t_pair *)map->members[i].pairs.ptr)[j].key);
			free(((t_pair *)map->members[i].pairs.ptr)[j].value);
			j++;
		}
		clear_vector(&map->members[i].pairs);
		i++;
	}
}
