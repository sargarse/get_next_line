/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:19:42 by sgarcia3          #+#    #+#             */
/*   Updated: 2024/01/09 19:22:31 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_buffer(char *buff, ssize_t *position)
{
	char	*line;
	ssize_t	i;

	i = 0;
	while (*(buff + *position + i) && *(buff + *position + i) != '\n')
	{
		/*if (*(buff + *position + i) == '\n')
			i++;*/
		i++;
	}
	if (*(buff + *position + i) == '\n')
		i++;
	/*if (*(buff + *position + i) == '\n' || *(buff + *position + i) == '\0')
		i++;*/
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(line, buff + *position, i + 1);
	//printf("position antes de incrementar: %ld\n", *position);
	*position += i;
	//printf("position despues de incrementar: %ld\n", *position);
	return (line);
}


char	*line_exceeds_buff(char *line, char *buff, ssize_t *position, int fd)
{
	char	buff_aux[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	ssize_t	len;
	char	*temp;

	while (*position == 0) {
		ft_bzero(buff_aux, BUFFER_SIZE + 1);
		bytes_read = read(fd, buff_aux, BUFFER_SIZE);
		if (bytes_read == -1) {
			if (line)
				free(line);
			ft_bzero(buff, BUFFER_SIZE + 1);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			printf("aquí\n");
			*position = -1;
			return (line);
		}
		buff_aux[bytes_read] = '\0';
		len = 0;
		while (*(buff_aux + len) && *(buff_aux + len) != '\n')
			len++;
		if (*(buff_aux + len) == '\n')
			len++;
		if (len < BUFFER_SIZE + 1)
		{
			ft_bzero(buff, BUFFER_SIZE + 1);
			ft_strlcpy_gnl(buff, buff_aux + len, (BUFFER_SIZE - len + 1));
		}
		temp = (char *)malloc(sizeof(char) * (len + 1));
		if (!temp)
			return (NULL);
		ft_strlcpy_gnl(temp, buff_aux, len + 1);
		line = ft_strjoin_gnl(line, temp, position);
		/*else if (bytes_read == 0)
		{
			*position = -1;
			return (NULL);
		}*/
		if (bytes_read < BUFFER_SIZE) {
			printf("aquí tambien\n");
			*position = -1;
		}
		/*if (len < BUFFER_SIZE + 1)
			ft_strlcpy_gnl(buff, buff_aux + len, (BUFFER_SIZE - len + 1));*/
	}
	*position = 0;

	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	static ssize_t	position;
	ssize_t		bytes_read;;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (position == 0 && buff[position] == '\0')
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1 || bytes_read == 0)
			return (NULL);
		buff[bytes_read] = '\0';
	}
	line = get_buffer(buff, &position);
	if (!line)
		return (NULL);
	printf("position: %ld\n", position);
	if (position != -1 && position > 0 && buff[position - 1] != '\n')
	{
		printf("Entra\n");
		ft_bzero(buff, BUFFER_SIZE + 1);
		position = 0;
		line = line_exceeds_buff(line, buff, &position, fd);
	}
	/*if (buff[position] == '\n')
		position++;*/
	return (line);
}