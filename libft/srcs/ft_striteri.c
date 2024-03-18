/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:08:47 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:02:29 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t i;
	if (!s || !f)
		return ; 
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]); 
		i++;
	}
	return;
}
