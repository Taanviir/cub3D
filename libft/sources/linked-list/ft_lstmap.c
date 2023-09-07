/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:31:38 by tanas             #+#    #+#             */
/*   Updated: 2023/07/29 13:08:38 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list 'lst' and applies the function 'f' to each element.
 * Creates a new list resulting from the successive applications of 'f'.
 *
 * @param lst The input list to iterate through.
 * @param f The function to apply to each element of the list.
 * @param del The function used to delete the content of an element if needed.
 * @return The new list, or NULL if memory allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	current = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&current, del);
			return (current);
		}
		ft_lstadd_back(&current, node);
		lst = lst->next;
	}
	return (current);
}
