/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:19:55 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:48:24 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int x;

	x = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		x++;
	}
	return(x);
}

















