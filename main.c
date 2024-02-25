/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:14:54 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/25 14:13:24 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "hashmap.h"
#include "get_next_line.h"

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

	prompt = "temp";
	while (prompt)
	{
		prompt = get_next_line(STDIN_FILENO);
		if (prompt == NULL || prompt[0] == '\n')
			break ;
		pair.key = prompt;
		pair.keyhash = hash_str(pair.key, NULL);
		prompt = get_next_line(STDIN_FILENO);
		pair.value = prompt;
		if (add_element(map, pair))
			return (-1);
	}
	free(prompt);
	return (0);
}

void	search_map(t_hashmap *map)
{
	char	*prompt;
	size_t	prompt_len;
	t_pair	*pair;
	t_hash	hash;

	prompt = "temp";
	while (prompt)
	{
		prompt = get_next_line(STDIN_FILENO);
		if (prompt == NULL)
			break ;
		hash = hash_str(prompt, &prompt_len);
		pair = get_element(map, hash, prompt);
		if (pair == NULL)
		{
			if (prompt[prompt_len - 1] == '\n')
				prompt_len -= 1;
			write(1, prompt, prompt_len);
			write(1, ": Not found.\n", 13);
		}
		else
			write(1, pair->value, ft_strlen(pair->value));
		free(prompt);
	}
}

int	print_errno(t_hashmap *map)
{
	char	*errno_str;

	clear_map(map);
	if (errno)
	{
		errno_str = strerror(errno);
		write(2, errno_str, ft_strlen(errno_str));
		write(2, "\n", 1);
		return (-1);
	}
	return (0);
}

int	main(void)
{
	static t_hashmap	map;

	if (fill_map(&map) == -1)
	{
		clear_map(&map);
		return (-1);
	}
	search_map(&map);
	print_errno(&map);
	return (0);
}
