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
	//int		fd2;
	char	*line;
	int		i;

	i = 0;
	//fd = open("alternate_line_nl_no_nl.txt", O_RDONLY);
	fd = open("multiple_nlx5.txt", O_RDONLY);
	//fd = open("archivo3.txt", O_RDONLY);
	//fd = open("archivo2.txt", O_RDONLY);
	//fd2 = open("archivo2.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i < 9)
	{
		line = get_next_line(fd);
		printf("linea: %s", line);
		free(line);
		//line = get_next_line(fd2);
		//printf("%s", line);
		//free(line);
		i++;
	}
	close (fd);
	return (0);
}
