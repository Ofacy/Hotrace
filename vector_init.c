/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:55:33 by lespenel          #+#    #+#             */
/*   Updated: 2024/01/15 06:22:41 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h" 

void	init_vector(t_vector *vector, size_t element_size)
{
	vector->element_size = element_size;
	vector->len = 0;
	vector->allocated = 0;
	vector->ptr = NULL;
}

void	*at_vector(t_vector *vector, size_t index)
{
	char	*element_address;

	element_address = (char *)vector->ptr + index * vector->element_size;
	return ((void *)element_address);
}
