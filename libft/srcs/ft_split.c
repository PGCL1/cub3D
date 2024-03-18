/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:37:27 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:00:52 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_pencilpushing(char const *s, char c)
{
	char	*str;
	int		i;
	int		n;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < n)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

static char	*ft_createordie(int n, char const *s, char c, char **token)
{
	token[n] = ft_pencilpushing(s, c);
	if (!token[n])
	{
		while (n > 0)
		{
			n--;
			free(token[n]);
		}	
		free(token);
		return (NULL);
	}
	return (token[n]);
}

static int	ft_words(char const *s, char c)
{
	int	n_words;

	n_words = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			n_words++;
		while (*s && *s != c)
			s++;
	}
	return (n_words);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		nb_words;
	char	**token;

	if (!s)
		return (NULL);
	j = 0;
	nb_words = ft_words(s, c);
	token = malloc(sizeof(char *) * (nb_words + 1));
	if (!token)
		return (NULL);
	while (j < nb_words)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			token[j] = ft_createordie(j, s, c, token);
		while (*s && *s != c)
			s++;
		j++;
	}
	token[j] = 0;
	return (token);
}
