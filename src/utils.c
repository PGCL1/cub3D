/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:31:54 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/21 18:46:26 by glacroix         ###   ########.fr       */
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
	array.len_len = 0;
	array.items = malloc(sizeof(array.items) * array.cap);
	array.items_len = malloc(sizeof(array.items_len) * array.cap);
	return (array);
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
	arr->len += 1;
}

void	ms_array_append_len(t_array *arr, size_t len)
{
	const size_t	size = sizeof(arr->items_len);

	if (!arr->items_len)
		return ;
	if (arr->cap == arr->len_len)
	{
		arr->cap *= 2;
		arr->items = ft_realloc(arr->items_len, arr->len * size, arr->cap * size);
		if (!arr->items_len)
			return ;
	}
	arr->items_len[arr->len_len] = len;
	arr->len_len += 1;
}
