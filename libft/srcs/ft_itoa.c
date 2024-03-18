/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:04:30 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:41:56 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t ft_count(int n)
{
	size_t len; 

	len = 1; 
	while (n /= 10)
		len++;
	return (len);
}

char *ft_itoa(int n)
{
	long 	num;
	char 	*str;
	size_t 	len;

	num = n;
	len = ft_count(n);
	if (n < 0)
	{
		num *= -1;
		len++;
	}	
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = num % 10 + '0'; 
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
