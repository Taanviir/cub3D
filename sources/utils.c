/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:11 by tanas             #+#    #+#             */
/*   Updated: 2023/11/05 21:45:48 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------- error utils ------------------------------ */

/**
 * @brief writes an error message
 *
 * @param error_msg message to write to stderr
 *
 * @return returns 0
 * */
int	write_error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	return (0);
}
