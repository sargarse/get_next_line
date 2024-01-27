/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia3 <sgarcia3@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:01:12 by sgarcia3          #+#    #+#             */
/*   Updated: 2023/12/09 01:23:51 by sgarcia3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("1char.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i < 2)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close (fd);
	return (0);
}
