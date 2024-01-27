/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:20:15 by sgarcia3          #+#    #+#             */
/*   Updated: 2024/01/09 00:27:18 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

void	ft_bzero(void *s, size_t n);
void	ft_strlcpy_gnl(char *dst, const char *src, ssize_t size);
char	*get_next_line(int fd);
char	*get_buffer(char *buff, ssize_t *position);
ssize_t	ft_strlen_gnl(const char *str);
char	*line_exceeds_buff(char *line, char *buff, ssize_t *position, int fd);
char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t *position);

#endif