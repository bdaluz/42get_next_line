/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:57:22 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/16 17:43:18 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int	fd;
	int	i;

	fd = open("teste.txt", O_RDONLY);
	i = 6;
	while (i--)
		get_next_line(fd);
	close(fd);
}
