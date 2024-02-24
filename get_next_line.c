/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:14:36 by lespenel          #+#    #+#             */
/*   Updated: 2024/01/07 22:53:10 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdlib.h"
#include <unistd.h>
#include <stddef.h>

int		join_line(t_buff *buff, char **line, size_t *line_len);
void	joinchr(t_buff *buff, size_t line_len, char **line, char **ptr);
ssize_t	read_lines(int fd, t_buff *buff);

char	*get_next_line(int fd)
{
	static t_buff	buff = {{0}, 0, 0};
	char			*line;
	size_t			line_len;
	char			*ptr;
	ssize_t			ret;

	line = NULL;
	line_len = 0;
	while (ft_strnchr(buff.buff + buff.start, \
					'\n', buff.end - buff.start) == NULL)
	{
		if (buff.end != buff.start)
			if (join_line(&buff, &line, &line_len) == -1)
				return (free(line), NULL);
		ret = read_lines(fd, &buff);
		if (ret < 0)
			return (buff.end = 0, free(line), NULL);
		if (ret == 0)
			return (line);
	}
	joinchr(&buff, line_len, &line, &ptr);
	if (line == NULL)
		return (free(line), NULL);
	return (buff.start = ptr - buff.buff, line);
}

ssize_t	read_lines(int fd, t_buff *buff)
{
	ssize_t	ret;

	(*buff).start = 0;
	ret = read(fd, (*buff).buff, BUFFER_SIZE);
	buff->end = ret;
	return (ret);
}

void	joinchr(t_buff *buff, size_t line_len, char **line, char **ptr)
{
	*ptr = ft_strnchr(buff->buff + buff->start, \
					'\n', \
					buff->end - buff->start) + 1;
	*line = ft_strn2join_free_s1(*line, \
								buff->buff + (*buff).start, \
								*ptr - (buff->buff + buff->start), \
								line_len);
}

int	join_line(t_buff *buff, char **line, size_t *line_len)
{
	*line = ft_strn2join_free_s1(*line, \
								buff->buff + buff->start, \
								buff->end - buff->start, \
								*line_len);
	*line_len += buff->end - buff->start;
	if (!(*line))
		return (-1);
	return (0);
}

char	*ft_strnchr(const char *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (s[i] != (char) c && i < n - 1)
		i++;
	if (s[i] == (char) c)
		return ((char *) s + i);
	else
		return (NULL);
}
