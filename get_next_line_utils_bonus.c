/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 11:45:43 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/23 21:32:29 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_frag	*get_after_newline(char *s)
{
	size_t	i;
	t_frag	*new_node;
	char	*new_content;

	while (*s && *s != '\n')
		s++;
	if (*s != '\n' || *(s + 1) == '\0')
		return (NULL);
	new_content = malloc(BUFFER_SIZE + 1);
	if (!new_content)
		return (NULL);
	new_node = malloc(sizeof(t_frag));
	if (!new_node)
	{
		free(new_content);
		return (NULL);
	}
	i = 0;
	while (s[++i])
		new_content[i - 1] = s[i];
	new_content[i - 1] = '\0';
	new_node->content = new_content;
	new_node->next = NULL;
	return (new_node);
}

void	clean_fragments(t_file *file)
{
	t_frag	*current;
	t_frag	*next;
	char	*new_content;

	current = file->fragments;
	while (current->next)
		current = current->next;
}

size_t	linelen(t_frag *fragments)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (fragments)
	{
		j = 0;
		while (fragments->content[j])
		{
			if (fragments->content[j] == '\n')
			{
				i++;
				return (i);
			}
			i++;
			j++;
		}
		fragments = fragments->next;
	}
	return (i);
}

int	has_newline(t_frag *fragments)
{
	size_t	i;

	while (fragments)
	{
		if (fragments->content)
		{
			i = 0;
			while (fragments->content[i])
			{
				if (fragments->content[i] == '\n')
					return (1);
				i++;
			}
		}
		fragments = fragments->next;
	}
	return (0);
}
