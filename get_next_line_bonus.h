/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bda-luz- <bda-luz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:45:59 by bda-luz-          #+#    #+#             */
/*   Updated: 2026/06/24 20:58:27 by bda-luz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_frag
{
	char			*content;
	struct s_frag	*next;
}					t_frag;

typedef struct s_file
{
	int				fd;
	t_frag			*fragments;
	struct s_file	*next;
}					t_file;

char	*get_next_line(int fd);
int		ft_has_newline(t_frag *fragments);
size_t	ft_linelen(t_frag *fragments);
void	ft_clean_fragments(t_file *file);

#endif
