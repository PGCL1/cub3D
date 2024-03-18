/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:24:54 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:47:36 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*newnode;

	if (!lst || !f)
		return (NULL);
	temp = NULL;
	while (lst)
	{
		newnode = ft_lstnew((*f)(lst->content));
		if (!newnode)
		{
			ft_lstclear(&temp, (del));
			return(NULL);
		}
		if (newnode)
			ft_lstadd_back(&temp, newnode);
		lst = lst->next;
	}
	return(temp);
}
