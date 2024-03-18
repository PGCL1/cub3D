/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:21:25 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:42:25 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{ 
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	return ;
}
