/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 01:32:03 by sabdelra          #+#    #+#             */
/*   Updated: 2022/12/09 18:14:40 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
int		new_line(char *stash);
void	*ft_memmove(void *dest, const void *src, size_t size);
char	*ft_strncat(char *dest, const char *src, size_t n);

#endif
