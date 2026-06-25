/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 11:26:04 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/24 22:02:27 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_file	*get_file(int fd, t_file **files)
{
	t_file	*current;
	t_file	*new_file;

	current = *files;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->fd = fd;
	new_file->fragments = NULL;
	new_file->next = *files;
	*files = new_file;
	return (new_file);
}

static char	*extract_line(t_file *file)
{
	t_frag	*fragments;
	size_t	line_len;
	size_t	i;
	size_t	j;
	char	*str;

	fragments = file->fragments;
	line_len = ft_linelen(fragments);
	if (line_len == 0)
		return (NULL);
	str = malloc(sizeof(char) * (line_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (fragments && i < line_len)
	{
		j = 0;
		while (fragments->content[j] && i < line_len)
			str[i++] = fragments->content[j++];
		fragments = fragments->next;
	}
	str[i] = '\0';
	return (str);
}

static t_frag	*append_fragment(t_file *file, char *buffer)
{
	t_frag	*new_node;
	t_frag	*current;

	new_node = malloc(sizeof(t_frag));
	if (!new_node)
	{
		free(buffer);
		return (NULL);
	}
	new_node->content = buffer;
	new_node->next = NULL;
	if (!file->fragments)
	{
		file->fragments = new_node;
		return (new_node);
	}
	current = file->fragments;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (new_node);
}

static int	build_fragment_list(int fd, t_file *files, int bytes_read)
{
	char	*buffer;
	t_frag	*new_frag;

	if (ft_has_newline(files->fragments))
		return (1);
	while (bytes_read > 0)
	{
		buffer = malloc((sizeof(char)) * BUFFER_SIZE + 1);
		if (!buffer)
			return (0);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			break ;
		}
		buffer[bytes_read] = '\0';
		new_frag = append_fragment(files, buffer);
		if (!new_frag)
			return (0);
		if (ft_has_newline(new_frag))
			break ;
	}
	return (bytes_read >= 0);
}

char	*get_next_line(int fd)
{
	static t_file	*open_files = NULL;
	t_file			*current_file;
	char			*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_file = get_file(fd, &open_files);
	if (!current_file)
		return (NULL);
	str = NULL;
	if (!build_fragment_list(fd, current_file, 1))
	{
		ft_remove_file(&open_files, fd);
		return (NULL);
	}
	str = extract_line(current_file);
	if (!str)
	{
		ft_remove_file(&open_files, fd);
		return (NULL);
	}
	ft_clean_fragments(current_file);
	return (str);
}
