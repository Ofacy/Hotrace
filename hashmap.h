/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:09:12 by lcottet           #+#    #+#             */
/*   Updated: 2024/02/25 13:55:08 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "vector.h"

# define HASHMAP_SIZE 100000

int		ft_strcmp(char *s1, char *s2);

typedef unsigned long	t_hash;
t_hash	hash_str(char *str, size_t *len);

typedef struct s_pair
{
	t_hash	keyhash;
	char	*key;
	char	*value;
}	t_pair;

typedef struct s_member
{
	t_vector	pairs;
}	t_member;

// data elements are vectors that allows collision checks.
typedef struct s_hashmap
{
	t_member	members[HASHMAP_SIZE];
}	t_hashmap;

int		add_element(t_hashmap *map, t_pair pair);
t_pair	*get_element(t_hashmap *map, t_hash hash, char *key);
void	clear_map(t_hashmap *map);

#endif
