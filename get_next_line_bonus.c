/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:48:46 by sgarcia3          #+#    #+#             */
/*   Updated: 2024/01/27 20:48:52 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*get_buffer(char *buff/*, ssize_t *position*/)
{
	char		*line;
	char		*buff_aux;
	ssize_t		i;
	ssize_t		len;

	i = 0;
	while (*(buff + i) && *(buff + i) != '\n')
		i++;
	if (*(buff + i) == '\n' || !*(buff + i))
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(line, buff, i + 1);
	len = ft_strlen_gnl(buff + i);
	buff_aux = (char *)malloc(sizeof(char) * (len + 1));
	if (!buff_aux)
		return (NULL);
	ft_strlcpy_gnl(buff_aux, buff + i, len + 1);
	ft_bzero(buff, BUFFER_SIZE + 1);
	ft_strlcpy_gnl(buff, buff_aux, len + 1);
	free(buff_aux);
	return (line);
}

char	*manage_aux(char *buff_aux, char *buff, char *line, ssize_t *position)
{
	ssize_t	len;
	char	*temp;

	len = 0;
	while (*(buff_aux + len) && *(buff_aux + len) != '\n')
		len++;
	if (*(buff_aux + len) == '\n')
		len++;
	if (len < BUFFER_SIZE + 1)
		ft_strlcpy_gnl(buff, buff_aux + len, (BUFFER_SIZE - len + 1));
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	ft_strlcpy_gnl(temp, buff_aux, len + 1);
	line = ft_strjoin_gnl(line, temp, position);
	return (line);
}

char	*line_exceeds_buff(char *line, char *buff/*, ssize_t *position*/, ssize_t *bytes_read, int fd)
{
	char	buff_aux[BUFFER_SIZE + 1];
	//ssize_t	bytes_read;
	ssize_t		position = 0;

	while (position == 0)
	{
		ft_bzero(buff_aux, BUFFER_SIZE + 1);
		*bytes_read = read(fd, buff_aux, BUFFER_SIZE);
		if (*bytes_read == -1 || (*bytes_read == 0 && ft_strlen_gnl(line) == 0))
		{
			free(line);
			return (NULL);
		}
		line = manage_aux(buff_aux, buff, line, &position);
		if (!line)
			return (NULL);
		if (*bytes_read < BUFFER_SIZE)
			position = -1;
	}
	position = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	//ssize_t			position;
	ssize_t			bytes_read;

	bytes_read = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buff[0] == '\0')
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1 || bytes_read == 0)
			return (NULL);
		buff[bytes_read] = '\0';
	}
	line = get_buffer(buff);
	//position = ft_strlen_gnl(buff);
	//printf("%ld\n", position);
	if (buff[0] == '\0' && bytes_read > 0)
	{
		//printf("Entra");
		ft_bzero(buff, BUFFER_SIZE + 1);
		//position = 0;
		line = line_exceeds_buff(line, buff/*, &position*/, &bytes_read, fd);
	}
	return (line);
}
