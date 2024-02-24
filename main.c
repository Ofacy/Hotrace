/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:14:54 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/24 17:14:37 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hashmap.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	fill_map(t_hashmap *map)
{
	char	*prompt;
	t_pair	pair;

	prompt = "ddd";
	while (prompt)
	{
		prompt = get_next_line(STDIN_FILENO);
		if (prompt == NULL || prompt[0] == '\n')
			break;
		pair.key = prompt;
		pair.keyhash = hash_str(pair.key, ft_strlen(pair.key));
		prompt = get_next_line(STDIN_FILENO);
		pair.value = prompt;
		if (add_element(map, pair))
			return (-1);
	}
	free(prompt);
	return (0);
}

int	search_map(t_hashmap *map)
{
	char	*prompt;
	t_pair	*pair;

	prompt = "ddd";
	while (prompt)
	{
		prompt = get_next_line(STDIN_FILENO);
		if (prompt == NULL)
			break;
		pair = get_element(map, prompt, ft_strlen(prompt));
		if (pair == NULL)
		{
			write(1, prompt, ft_strlen(prompt) - 1);
			write(1, ": Not found.\n", 13);
		}
		else
		{
			write(1, pair->value, ft_strlen(pair->value));
		}
		free(prompt);
	}
	return (0);
}

int	main(void)
{
	t_hashmap	map;

	if (init_map(&map, 100000))
		return (-1);
	if (fill_map(&map) == -1)
		return (-1);
	if (search_map(&map) == -1)
		return (-1);
	clear_map(&map);
	return (0);
}
