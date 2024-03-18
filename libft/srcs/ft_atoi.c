/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:05:05 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:11:48 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"


int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned int	re;

	i = 0;
	re = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		re = ((str[i++] - '0') + (re * 10));
	if (re > 2147483647 && sign == 1)
		return (-1);
	else if (re > 2147483648 && sign == -1)
		return (0);
	return ((int) re * sign);
}
