/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:04:54 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:43:56 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void*))
{	
	if (!lst)
		return ;
	if (lst)
		del(lst->content);
	free(lst);
	return ;
}
