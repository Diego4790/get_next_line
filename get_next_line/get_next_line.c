/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dileleux <dileleux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:05:19 by dileleux          #+#    #+#             */
/*   Updated: 2021/03/15 12:01:46 by dileleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_free_if_freeable(char **to_free, int return_flag)
{
	if (*to_free)
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

	temp = *line;
	if ((newline_pointer = ft_strchr(*variable, '\n')))
	{
		*newline_pointer = '\0';
		*line = ft_strdup(*variable);
		ft_free_if_freeable(variable, 0);
		*variable = ft_strdup(++newline_pointer);
		ft_free_if_freeable(&temp, 0);
		return (1);
	}
	*line = ft_strdup(*variable);
	ft_free_if_freeable(variable, 0);
	ft_free_if_freeable(&temp, 0);
	return (0);
}

static int	ft_concat_until_newline(char **line, char **buf, char **variable)
{
	char *newline_pointer;
	char *temp;

	temp = *line;
	if ((newline_pointer = ft_strchr(*buf, '\n')))
	{
		*newline_pointer = '\0';
		*variable = ft_strdup(++newline_pointer);
	}
	*line = ft_strjoin(*line, *buf);
	ft_free_if_freeable(&temp, 0);
	if (newline_pointer)
		return (0);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		*buf;
	int			bytes_read;
	static char	*variable;

	if (fd < 0 || fd >= FOPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	*line = ft_calloc(sizeof(char), 1);
	if (variable && ft_remaining_newline(&variable, line))
		return (1);
	if (!(buf = (char*)malloc(sizeof(*buf) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((bytes_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_read] = '\0';
		if (ft_concat_until_newline(line, &buf, &variable))
			continue ;
		return (ft_free_if_freeable(&buf, 1));
	}
	return (ft_free_if_freeable(&buf, bytes_read));
}
