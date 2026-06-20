/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:46:02 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/20 18:56:12 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_gnl(int fd, char *stash)
{
	int		bytes_read;
	char	*temp_buffer;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		stash = ft_strjoin_gnl(stash, temp_buffer);
		if (!stash || ft_strchr(stash, '\n'))
			break ;
	}
	free(temp_buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*str;
	size_t	line_size;

	if (!stash || stash[0] == '\0')
		return (NULL);
	line_size = ft_strclen_gnl(stash, '\n');
	if (stash[line_size] == '\n')
		line_size++;
	str = ft_substr(stash, 0, line_size);
	if (!str)
		return (NULL);
	return (str);
}

static char	*clean_stash(char *stash)
{
	char	*temp;
	size_t	line_size;

	line_size = ft_strclen_gnl(stash, '\n');
	if (stash[line_size] == '\n')
		line_size++;
	temp = ft_substr(stash, line_size, ft_strclen_gnl(stash, '\0') - line_size);
	free(stash);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_gnl(fd, stash);
	if (!stash)
		return (NULL);
	str = extract_line(stash);
	if (!str)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (str);
}
