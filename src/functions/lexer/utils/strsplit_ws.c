/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:37:56 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/06 20:41:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		ft_is_space(char c)
{
	return (c != '\0' &&
	(
		c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' '));
}

static char		let_n_char(char *s, size_t id_w, size_t id_c)
{
	int		i;
	size_t	n_words;
	size_t	n_chars;

	i = 0;
	n_words = 0;
	n_chars = 0;
	while (s[i])
	{
		while (ft_is_space(s[i]) && !lexer_is_esc(s, i))
			i++;
		if (s[i])
			n_words++;
		while (s[i] && (!ft_is_space(s[i]) || lexer_is_esc(s, i)))
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

static size_t	get_n_chars(char *s, size_t id_word)
{
	int		i;
	size_t	n_words;
	size_t	n_chars;

	i = 0;
	n_words = 0;
	n_chars = 0;
	while (s[i])
	{
		while (ft_is_space(s[i]) && !lexer_is_esc(s, i))
			i++;
		if (s[i])
			n_words++;
		while (s[i] && (!ft_is_space(s[i]) || lexer_is_esc(s, i)))
		{
			if (id_word == n_words)
				n_chars++;
			i++;
		}
	}
	return (n_chars);
}

static size_t	get_n_words(char *s)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (ft_is_space(s[i]) && !lexer_is_esc(s, i))
			i++;
		if (s[i])
			n++;
		while (s[i] && (!ft_is_space(s[i]) || lexer_is_esc(s, i)))
			i++;
	}
	return (n);
}

char			**lexer_strsplit_ws(char *s)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s)
		return (NULL);
	if (!(ptr = (char **)malloc(sizeof(*ptr) * (get_n_words(s) + 1))))
		return (NULL);
	while (i < get_n_words(s))
	{
		if (!(ptr[i] = (char *)malloc(sizeof(char) * (get_n_chars(s, i + 1)
		+ 1))))
			return (NULL);
		j = 0;
		while (j < get_n_chars(s, i + 1))
		{
			ptr[i][j] = let_n_char(s, i + 1, j + 1);
			j++;
		}
		ptr[i][j] = '\0';
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
