/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:20:28 by sgarcia3          #+#    #+#             */
/*   Updated: 2024/01/09 00:21:44 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	int fd;
	char *line;

	fd = open("archivo.txt", O_RDONLY);
	if (fd == -1)
		return 1;

	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}

	close(fd);
	return 0;
}
