/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 01:43:38 by tanas             #+#    #+#             */
/*   Updated: 2023/07/27 01:43:38 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees memory allocated to a double pointer and sets it to NULL.
 *
 * @param double_ptr The double pointer to free.
 */
void	ft_free_double(void **double_ptr)
{
	int	i;

	if (!double_ptr || !(*double_ptr))
		return ;
	i = 0;
	while (double_ptr[i])
	{
		free(double_ptr[i]);
		i++;
	}
	free(double_ptr);
}
