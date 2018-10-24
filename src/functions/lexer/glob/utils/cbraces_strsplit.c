/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:02:47 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:58:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool		in_cbrace(char *s, int position)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && i < position)
	{
		if (s[i] == '{')
			count++;
		else if (s[i] == '}')
			count--;
		i++;
	}
	return (count > 0);
}

static char		let_n_char(char *s, char c, size_t id_w, size_t id_c)
{
	int		i;
	size_t	n_words;
	size_t	n_chars;

	i = 0;
	n_words = 0;
	n_chars = 0;
	while (s[i])
	{
		while (s[i] == c && !lexer_is_esc(s, i) && !in_cbrace(s, i))
			i++;
		if (s[i])
			n_words++;
		while (s[i] && (s[i] != c || lexer_is_esc(s, i) || in_cbrace(s, i)))
		{
			if (id_w == n_words)
			{
				n_chars++;
				if (n_chars == id_c)
					return (s[i]);
			}
			i++;
		}
	}
	return (0);
}

static size_t	get_n_chars(char *s, char c, size_t id_word)
{
	int		i;
	size_t	n_words;
	size_t	n_chars;

	i = 0;
	n_words = 0;
	n_chars = 0;
	while (s[i])
	{
		while (s[i] == c && !lexer_is_esc(s, i) && !in_cbrace(s, i))
			i++;
		if (s[i])
			n_words++;
		while (s[i] && (s[i] != c || lexer_is_esc(s, i) || in_cbrace(s, i)))
		{
			if (id_word == n_words)
				n_chars++;
			i++;
		}
	}
	return (n_chars);
}

static size_t	get_n_words(char *s, char c)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c && !lexer_is_esc(s, i) && !in_cbrace(s, i))
			i++;
		if (s[i])
			n++;
		while (s[i] && (s[i] != c || lexer_is_esc(s, i) || in_cbrace(s, i)))
			i++;
	}
	return (n);
}

char			**cbraces_strsplit(char *s, char c)
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
