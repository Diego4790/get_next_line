/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dileleux <dileleux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:05:19 by dileleux          #+#    #+#             */
/*   Updated: 2021/05/14 23:52:13 by dileleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_free_if_freeable(char **to_free, int return_flag)
{
	if (to_free != NULL && *to_free != NULL)
	{
		free(*to_free);
		*to_free = NULL;
	}
	return (return_flag);
}

static int	ft_remaining_newline(char **variable, char **line)
{
	char	*newline_pointer;
	char	*temp;

	ft_free_if_freeable(line, 0);
	newline_pointer = ft_strchr(*variable, '\n');
	if (newline_pointer)
	{
		*newline_pointer = '\0';
		*line = ft_strdup(*variable);
		temp = *variable;
		*variable = ft_strdup(++newline_pointer);
		ft_free_if_freeable(&temp, 0);
		return (1);
	}
	*line = ft_strdup(*variable);
	ft_free_if_freeable(variable, 0);
	return (0);
}

static int	ft_concat_until_newline(char **line, char *buf, char **variable)
{
	char	*newline_pointer;
	char	*temp;

	temp = *line;
	newline_pointer = ft_strchr(buf, '\n');
	if (newline_pointer)
	{
		*newline_pointer = '\0';
		*variable = ft_strdup(++newline_pointer);
	}
	*line = ft_strjoin(*line, buf);
	ft_free_if_freeable(&temp, 0);
	if (newline_pointer)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	int			bytes_read;
	static char	*variable[OPEN_MAX];

	bytes_read = 1;
	if (fd < 0 || !line || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX || \
			fd >= OPEN_MAX)
		return (-1);
	*line = ft_calloc(sizeof(char), 1);
	if (variable[fd] && ft_remaining_newline(&variable[fd], line))
		return (1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (ft_concat_until_newline(line, buf, &variable[fd]))
			continue ;
		return (ft_free_if_freeable(&buf, 1));
	}
	return (ft_free_if_freeable(&buf, bytes_read));
}
