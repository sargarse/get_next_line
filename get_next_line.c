/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:47:28 by sgarcia3          #+#    #+#             */
/*   Updated: 2023/12/09 02:14:58 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = 0;
		i++;
	}
}

ssize_t	read_fd(int fd, char **buff_ptr)
{
	ssize_t	ctrl;
	char	*buff;

	buff = *buff_ptr;
	ctrl = read(fd, buff, BUFFER_SIZE);
	if (ctrl < 0)
	{
		free(buff);
		buff = NULL;
		return (-1);
	}
	if (ctrl > 0)
		buff[ctrl] = '\0';
	*buff_ptr = buff;
	return (ctrl);
}

char	*read_line(char **buff, int fd)
{
	char	*ptrln;
	char	*line = "";
	ssize_t	ctrl;
	char	*tmp;

	ctrl = read_fd(fd, &*buff);
	if (ctrl < 1) {
		return (NULL);
	}
	while ((ptrln = ft_strchr(*buff, '\n')) == NULL && ctrl > 0)
	{
		line = ft_strjoin(line, *buff);
		ctrl = read_fd(fd, &*buff);
		if (ctrl == -1)
			return (NULL);
	}
	if ((ptrln = ft_strchr(*buff, '\n')))
	{
		tmp = ft_substr(*buff, 0, ptrln - *buff);
		line = ft_strjoin(line, tmp);
		ft_memmove(*buff, ptrln + 1, ft_strlen(ptrln + 1));
		ft_bzero(*buff + ft_strlen(ptrln + 1), BUFFER_SIZE - ft_strlen(ptrln + 1));
	}
	if (ctrl < 0)
		return (NULL);
	return (line);
}

char *get_next_line(int fd) {
	static char *buff;
	char *line;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buff)
	{
		buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		buff[0] = '\0';
	}
	line = read_line(&buff, fd);
	return (line);
}