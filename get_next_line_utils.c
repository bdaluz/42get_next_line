/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:59:08 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/25 23:31:01 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_linelen(t_list *list)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (list)
	{
		j = 0;
		while (list->fragment[j])
		{
			if (list->fragment[j] == '\n')
			{
				i++;
				return (i);
			}
			i++;
			j++;
		}
		list = list->next;
	}
	return (i);
}

int	ft_has_newline(t_list *list)
{
	size_t	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->fragment[i])
		{
			if (list->fragment[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

static t_list	*ft_get_after_newline(char *fragment)
{
	char	*str;
	t_list	*new_node;
	size_t	i;

	while (*fragment && *fragment != '\n')
		fragment++;
	if (*fragment != '\n' || *(fragment + 1) == '\0')
		return (NULL);
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (fragment[++i])
		str[i - 1] = fragment[i];
	str[i - 1] = '\0';
	new_node->fragment = str;
	new_node->next = NULL;
	new_node->tail = NULL;
	return (new_node);
}

void	ft_free_fragments(t_list **list)
{
	t_list	*new_node;
	t_list	*next;

	if (!list || !*list || !(*list)->fragment)
		return ;
	new_node = ft_get_after_newline((*list)->tail->fragment);
	while (*list)
	{
		next = (*list)->next;
		free((*list)->fragment);
		free(*list);
		*list = next;
	}
	*list = new_node;
	if (*list)
		(*list)->tail = new_node;
}
