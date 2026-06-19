/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:46:02 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/19 19:45:41 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*temp_buffer;
	char		*str;
	int			b;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	b = read(fd, temp_buffer, BUFFER_SIZE);
	if (b < 0)
	{
		free(temp_buffer);
		return (NULL);
	}
	temp_buffer[b] = '\0';
	while (b > 0)
	{
		
	}
	return (str);
}
