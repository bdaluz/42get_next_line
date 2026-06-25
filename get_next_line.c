/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:58:59 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/25 18:39:34 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(t_list *list)
{
	char	*str;
	size_t	line_len;
	size_t	i;
	size_t	j;

	line_len = ft_linelen(list);
	if (line_len == 0)
		return (NULL);
	str = malloc(sizeof(char) * (line_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (list && i < line_len)
	{
		j = 0;
		while (list->fragment[j] && i < line_len)
		{
			str[i] = list->fragment[j];
			i++;
			j++;
		}
		list = list->next;
	}
	str[i] = '\0';
	return (str);
}

static t_list	*append_or_create(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*current;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buffer);
		return (NULL);
	}
	new_node->fragment = buffer;
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return (new_node);
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (new_node);
}

static int	build_fragments(int fd, t_list **list, int bytes_read)
{
	char	*buffer;
	t_list	*new_node;

	if (ft_has_newline(*list))
		return (1);
	while (bytes_read > 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (0);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			break ;
		}
		buffer[bytes_read] = '\0';
		new_node = append_or_create(list, buffer);
		if (!new_node)
			return (0);
		if (ft_has_newline(new_node))
			break ;
	}
	return (bytes_read >= 0);
}

char	*get_next_line(int fd)
{
	static t_list	*fragments = NULL;
	char			*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!build_fragments(fd, &fragments, 1))
	{
		ft_free_fragments(&fragments);
		return (NULL);
	}
	str = get_line(fragments);
	if (!str)
	{
		ft_free_fragments(&fragments);
		return (NULL);
	}
	ft_free_fragments(&fragments);
	return (str);
}
