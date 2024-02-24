/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:14:54 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/24 19:57:57 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hashmap.h"
#include <errno.h>

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
	size_t	line_len;

	line_len = 0;
	prompt = "ddd";
	while (prompt)
	{
		prompt = get_next_line(STDIN_FILENO);
		if (prompt == NULL || prompt[0] == '\n')
			break ;
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

void	search_map(t_hashmap *map)
{
	char	*prompt;
	t_pair	*pair;
	size_t	line_len;

	line_len = 0;
	prompt = "ddd";
	while (prompt)
	{
		prompt = get_next_line(STDIN_FILENO);
		if (prompt == NULL)
			break ;
		pair = get_element(map, prompt, ft_strlen(prompt));
		if (pair == NULL)
		{
			write(1, prompt, strlen(prompt) - 1);
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
