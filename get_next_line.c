/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:46:02 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/20 23:07:40 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stash = NULL;
	char		*str;
	size_t		line_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash || !ft_strchr(stash, '\n'))
		stash = read_gnl(fd, stash, 1);
	if (!stash)
		return (NULL);
	line_size = ft_strclen_gnl(stash, '\n');
	if (stash[line_size] == '\n')
		line_size++;
	str = extract_line(stash, line_size);
	if (!str)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash, line_size);
	return (str);
}
