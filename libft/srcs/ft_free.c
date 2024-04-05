/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:21:14 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/05 17:26:49 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	*ft_free(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i] != NULL)
	{
		//printf("ptr[%d] = %s\n", i, ptr[i]);
		free(ptr[i]);
		ptr[i] = NULL;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}
