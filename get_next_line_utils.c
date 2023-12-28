/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:44:06 by sgarcia3          #+#    #+#             */
/*   Updated: 2023/12/09 01:55:54 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;
	char	*tmp;
	
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(len + 1);
	tmp = ptr;
	if (ptr == NULL)
		return (NULL);
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (tmp);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp;
	
	tmp = dst;
	if (!dst && !src)
		return (dst);
	if (dst == src)
		return (dst);
	if (src < dst)
		while (len--)
			*((char *)dst + len) = *((char *)src + len);
	else
		while (len--)
			*(char *)dst++ = *(char *)src++;
	return (tmp);
}

size_t	ft_strlen(const char *src)
{
	size_t	i;
	
	i = 0;
	while (*(src + i))
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		dst = malloc(sizeof(char) * 1);
		if (!dst)
			return (NULL);
	}
	else
	{
		if (ft_strlen(s + start) < len)
			len = ft_strlen(s + start);
		dst = malloc(sizeof(char) * (len + 1));
		if (!dst)
			return (NULL);
		ft_memmove(dst, s + start, len);
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	
	tmp = (char *)s;
	while (*tmp)
	{
		if (*tmp == (char)c)
			return (tmp);
		tmp++;
	}
	if ((char)c == '\0')
		return (tmp);
	return (NULL);
}
