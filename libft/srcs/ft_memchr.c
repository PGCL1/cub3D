/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:41:11 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/27 19:07:49 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s)[0]) == (unsigned char) c)
			return ((unsigned char *)s + i);
		i++;
	}
	return (0);
}

//typedef struct s_test {
	//char a;
	//long b;
//}	t_test;



//int main()
//{
	//t_test test;
	//ft_memset(&test, 0, sizeof(test));
	////printf("test.a = %c test.a = %p\n",test.a,  &test.a);
	//printf("%s\n", ft_memchr(&test, 0, sizeof(test)));
	//return 0;
//}
