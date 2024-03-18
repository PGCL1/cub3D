/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:02:24 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:28:22 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isnumber(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!str)
		return (0);
	len = ft_strlen(str);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < len)
	{
		if ((i < 3) && str[i] == '.' && ft_isdigit(str[i + 1]) == 1)
			i++;
		else if ((i < 3) && ft_isdigit(str[i]) == 1 && str[i + 1] == '.')
			i += 2;
		else if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
