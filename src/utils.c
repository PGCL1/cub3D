/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:54 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/25 16:16:09 by glacroix         ###   ########.fr       */
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
	size_t i = 0;
	if (!item)
		return (0);
	while (item[i] != '\n' && item[i] != '\0')
		i++;
	return (i);
}

void	ms_array_append(t_array *arr, char *item)
{
	const size_t	size = sizeof(arr->items);

	if (!arr->items)
		return ;
	if (arr->cap == arr->len)
	{
		arr->cap *= 2;
		arr->items = ft_realloc(arr->items, arr->len * size, arr->cap * size);
		if (!arr->items)
			return ;
	}
	arr->items[arr->len] = item;
	arr->items_len[arr->len] = 0;
	arr->items_len[arr->len] = line_len(item);
	arr->len += 1;
}

