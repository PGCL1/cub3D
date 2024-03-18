/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:25:31 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:42:37 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	new -> next = *lst;
	*lst = new;
}
