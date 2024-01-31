/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:19:42 by sgarcia3          #+#    #+#             */
/*   Updated: 2024/01/26 23:09:28 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer(char *buff)
{
	char	*line;
	char	*buff_aux;
	ssize_t	i;
	ssize_t	len;

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

ssize_t	find_len(char *buff_aux)
{
	ssize_t	len;

	len = 0;
	while (*(buff_aux + len) && *(buff_aux + len) != '\n')
		len++;
	if (*(buff_aux + len) == '\n')
		len++;
	return (len);
}

char	*line_exceeds_buff(char *line, char *buff, ssize_t *bytes_read, int fd)
{
	char		buff_aux[BUFFER_SIZE + 1];
	ssize_t		position;
	ssize_t		len;

	position = 0;
	while (position == 0)
	{
		ft_bzero(buff_aux, BUFFER_SIZE + 1);
		*bytes_read = read(fd, buff_aux, BUFFER_SIZE);
		if (*bytes_read == -1 || (*bytes_read == 0 && ft_strlen_gnl(line) == 0))
		{
			free(line);
			return (NULL);
		}
		len = find_len(buff_aux);
		line = ft_strjoin_gnl(line, buff_aux, &position, len);
		if (len < BUFFER_SIZE)
			ft_strlcpy_gnl(buff, buff_aux + len, (BUFFER_SIZE - len + 1));
		if (*bytes_read < BUFFER_SIZE)
			position = -1;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	ssize_t			bytes_read;

	bytes_read = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_buffer(buff);
	if (buff[0] == '\0')
		line = line_exceeds_buff(line, buff, &bytes_read, fd);
	return (line);
}
