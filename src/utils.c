/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:54 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 21:10:51 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_realloc(void *ptr, size_t len, size_t size)
{
	void	*new;

	if (size == 0)
		return (NULL);
	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, len);
		free(ptr);
	}
	return (new);
}

t_array	ms_array_init(void)
{
	t_array	array;

	array.cap = 2;
	array.len = 0;
	array.items = malloc(sizeof(array.items) * array.cap);
	array.items_len = malloc(sizeof(array.items_len) * array.cap);
	return (array);
}

size_t	line_len(char *item)
{
	size_t	i;

	i = 0;
	if (!item)
		return (0);
	while (item[i] != '\n' && item[i] != '\0')
		i++;
	return (i);
}

void	ms_array_append(t_array *a, char *item)
{
	const size_t	size = sizeof(a->items);

	if (!a->items)
		return ;
	if (a->cap == a->len)
	{
		a->cap *= 2;
		a->items = ft_realloc(a->items, a->len * size, a->cap * size);
		if (!a->items)
			return ;
		a->items_len = ft_realloc(a->items_len, a->len * size, a->cap * size);
		if (!a->items_len)
			return ;
	}
	a->items[a->len] = item;
	a->items_len[a->len] = line_len(item);
	a->len += 1;
}

void	error_msg(char *msg)
{
	ft_putstr_fd(P_RED"Error: "RESET, 2);
	ft_putendl_fd(msg, 2);
}
