/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:30:17 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 12:57:03 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds a new element to the end of a linked list.
 *
 * @param lst A pointer to the address of the first element in the list.
 * @param new The new element to add.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst)
		return ;
	if (*lst)
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
	else
		*lst = new;
}
