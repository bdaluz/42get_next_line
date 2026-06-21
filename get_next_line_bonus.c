/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:46:02 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/20 23:34:54 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_gnl(int fd, char *stash, long bytes_read)
{
	char	*temp_buffer;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
	{
		free(stash);
		return (NULL);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		stash = ft_strjoin_gnl(stash, temp_buffer);
		if (!stash || ft_strchr(temp_buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	if (bytes_read < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

static char	*extract_line(char *stash, size_t line_size)
{
	char	*str;

	if (!stash || stash[0] == '\0')
		return (NULL);
	str = ft_substr_gnl(stash, 0, line_size);
	if (!str)
		return (NULL);
	return (str);
}

static char	*clean_stash(char *stash, size_t line_size)
{
	char	*temp;
	size_t	stash_len;

	stash_len = ft_strclen_gnl(stash, '\0');
	if (stash_len == line_size)
	{
		free(stash);
		return (NULL);
	}
	temp = ft_substr_gnl(stash, line_size, stash_len - line_size);
	free(stash);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*str;
	size_t		line_size;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd] || !ft_strchr(stash[fd], '\n'))
		stash[fd] = read_gnl(fd, stash[fd], 1);
	if (!stash[fd])
		return (NULL);
	line_size = ft_strclen_gnl(stash[fd], '\n');
	if (stash[fd][line_size] == '\n')
		line_size++;
	str = extract_line(stash[fd], line_size);
	if (!str)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd], line_size);
	return (str);
}
