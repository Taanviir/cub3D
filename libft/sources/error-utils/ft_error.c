/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:50:52 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 01:58:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints an error message to stderr and exits with the given error code.
 * 
 * @param message Error message to display.
 * @param err Error code to use for the process exit.
 */

void	ft_error(char *message, int err)
{
	ft_putendl_fd(message, 2);
	exit(err);
}
