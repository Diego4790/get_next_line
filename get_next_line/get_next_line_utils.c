/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dileleux <dileleux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:06:34 by dileleux          #+#    #+#             */
/*   Updated: 2021/03/15 11:02:15 by dileleux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	i;

	i = 0;
	if (!(array = malloc(nmemb * size)))
		return (NULL);
	while (i < size)
	{
		((unsigned char*)array)[i] = 0;
		i++;
	}
	return (array);
}

char	*ft_strchr(const char *str, int c)
{
	char	*s;
	int		i;

	i = 0;
	s = (char*)str;
	while (s && s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s || !(str = malloc(sizeof(*str) * ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(*str) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
