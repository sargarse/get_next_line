/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 19:44:45 by sgarcia3          #+#    #+#             */
/*   Updated: 2023/12/28 19:45:36 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char **buffer, int fd)
{
	char	*line;
	ssize_t	ctrl;
	char	*ptrln;
	char	*tmp;
	
	ctrl = 1;
	line = (char *)malloc(sizeof(char));
	if (!line)
	{
		return (NULL);
		free(*buffer);
	}
	line = "";
	while (ft_strchr(*buffer, '\n') == NULL)
	{
		line = ft_strjoin(line, *buffer);
		ctrl = read(fd, *buffer, BUFFER_SIZE);
		if (ctrl == -1 || ctrl == 0)
		{
			free(line);
			return (NULL);
		}
	}
	if ((ptrln = ft_strchr(*buffer, '\n')))
	{
		tmp = ft_substr(*buffer, 0, ptrln - *buffer);
		line = ft_strjoin(line, tmp);
		*buffer = ptrln + 1;
		free(tmp);
	}
	return (line);
}
char	*get_next_line(int fd)
{
	static char *buffer;
	char 		*line;
	
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	line = read_line(&buffer, fd);
	return (line);
}