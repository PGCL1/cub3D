/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:37:46 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:43:37 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = temp->next;
		ft_lstdelone(temp, (*del));
	}
}
