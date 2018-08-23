/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:58:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/04 12:47:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		let_n_char(char const *s, char c, size_t id_w, size_t id_c)
{
	size_t	n_words;
	size_t	n_chars;

	n_words = 0;
	n_chars = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			n_words++;
		while (*s != c && *s)
		{
			if (id_w == n_words)
			{
				n_chars++;
				if (n_chars == id_c)
					return (*s);
			}
			s++;
		}
	}
	return (0);
}

static size_t	get_n_chars(char const *s, char c, size_t id_word)
{
	size_t	n_words;
	size_t	n_chars;

	n_words = 0;
	n_chars = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			n_words++;
		while (*s != c && *s)
		{
			if (id_word == n_words)
				n_chars++;
			s++;
		}
	}
	return (n_chars);
}

static size_t	get_n_words(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			n++;
		while (*s && *s != c)
			s++;
	}
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s)
		return (NULL);
	if (!(ptr = (char **)malloc(sizeof(*ptr) * (get_n_words(s, c) + 1))))
		return (NULL);
	while (i < get_n_words(s, c))
	{
		if (!(ptr[i] = (char *)malloc(sizeof(char) * (get_n_chars(s, c, i + 1)
		+ 1))))
			return (NULL);
		j = 0;
		while (j < get_n_chars(s, c, i + 1))
		{
			ptr[i][j] = let_n_char(s, c, i + 1, j + 1);
			j++;
		}
		ptr[i][j] = '\0';
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
