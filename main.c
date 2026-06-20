/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:57:22 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/20 16:50:25 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*str;

	fd = open("teste.txt", O_RDONLY);
	i = 0;
	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	printf("fd: %d\n", fd);
	while (i++ < 100)
	{
		str = get_next_line(fd);
		if (!str)
			printf("NULL or EOF\n");
		else
		{
			printf("%d --> %s", i, str);
			free(str);
		}
	}
	close(fd);
}
