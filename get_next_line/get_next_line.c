/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 01:33:11 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/09 18:08:03 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
[to-do] initializing on the stack
[to-do] debug and optimzie
[to-do] destroy and re-create
 */
#include "get_next_line.h"

static char	*shift_left(char **stash);
static void	join(char **stash, char *buffer, int buffer_length);

char	*get_next_line(int fd)
{
	static char		*stash;
	int				read_return;
	char			buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	if (!stash)
		stash = "";
	read_return = 1;
	while (new_line(stash) == 0 && read_return > 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return < 0)
			return (NULL);
		buffer[read_return] = '\0';
		join(&stash, buffer, read_return + 1);
	}
	if (!stash)
		return (NULL);
	return (shift_left(&stash));
}

static char	*shift_left(char **stash)
{
	char	*return_string;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((*stash)[i] != '\n' && (*stash)[i])
		i++;
	return_string = (char *)malloc(i + 2);
	if (!return_string)
		return (0);
	ft_memmove(return_string, *stash, i + 1);
	return_string[i + 1] = '\0';
	while ((*stash)[i + j++])
		;
	ft_memmove(*stash, *stash + i + 1, j);
	if (*stash && !**stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (return_string);
}

static void	join(char **stash, char *buffer, int buffer_length)
{
	char	*new_stash;
	size_t	stash_length;

	if (*stash)
		stash_length = ft_strlen(*stash);
	else
		stash_length = 0;
	new_stash = (char *)malloc(stash_length + buffer_length + 1);
	if (!new_stash)
		return ;
	ft_memmove(new_stash, *stash, stash_length + 1);
	ft_strncat(new_stash, buffer, buffer_length);
	new_stash[stash_length + buffer_length] = '\0';
	if (**stash)
		free(*stash);
	*stash = new_stash;
	if (new_stash[0] == '\0')
	{
		free(new_stash);
		*stash = NULL;
	}
}
