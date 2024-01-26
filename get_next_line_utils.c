/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:20:03 by sgarcia3          #+#    #+#             */
/*   Updated: 2024/01/09 13:55:01 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t *position)
{
	size_t	len;
	size_t	i;
	char	*ptr;
	char	*tmp;
	
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	tmp = ptr;
	i = 0;
	while (*(s1 + i))
	{
		*ptr++ = *(s1 + i);
		i++;
	}
	if (s1)
		free(s1);
	i = 0;
	while (*(s2 + i)) {
		*ptr++ = *(s2 + i);
		i++;
	}
	*ptr = '\0';
	if (*(tmp + len - 1) == '\n')
	{
		*position = ft_strlen_gnl(s2);
	}
	free(s2);
	return (tmp);
}

ssize_t	ft_strlen_gnl(const char *str)
{
	ssize_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

void	ft_strlcpy_gnl(char *dst, const char *src, ssize_t size)
{
	ssize_t	i;

	if (!dst || !src)
		return ;
	i = 0;
	if (size > 0)
	{
		while (i < (size - 1) && *(src + i))
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
}