/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:44:47 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/24 15:37:39 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

int	free_vector(t_vector *vector);
int	resize_vector(t_vector *vector);

int	add_vector(t_vector *vector, void *new_content)
{
	size_t	i;

	if (resize_vector(vector))
		return (1);
	i = 0;
	while (i != vector->element_size)
	{
		*((char *)(vector->ptr + (vector->len * vector->element_size) + i)) \
			= *((char *)(new_content + i));
		i++;
	}
	vector->len += 1;
	return (0);
}

int	resize_vector(t_vector *vector)
{
	void	*temp;

	temp = NULL;
	if (vector->len == vector->allocated)
	{
		if (vector->allocated == 0)
			vector->allocated = 16;
		else
			vector->allocated *= 2;
		temp = malloc(vector->element_size * vector->allocated);
		if (temp == NULL)
			if (free_vector(vector))
				return (1);
		ft_memcpy(temp, vector->ptr, vector->element_size * vector->len);
		free(vector->ptr);
		vector->ptr = temp;
	}
	return (0);
}

int	free_vector(t_vector *vector)
{
	if (vector->ptr)
		free(vector->ptr);
	return (1);
}
