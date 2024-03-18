/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:35:24 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 15:57:54 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_uns(unsigned int nbr)
{
	int	n;

	n = 0;
	if (nbr > 9)
		n += ft_putnbr_uns(nbr / 10);
	return (n += ft_putchar(nbr % 10 + '0'));
}
