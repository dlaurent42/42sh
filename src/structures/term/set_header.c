/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 20:21:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 12:34:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned char	*sh_get_folder_name(unsigned char *str, size_t len)
{
	while (str[len] && str[len] != '/')
		len--;
	return ((unsigned char *)ft_strdups((char *)(str + len + 1)));
}

static size_t			sh_count_slash(unsigned char *str)
{
	unsigned char	i;
	unsigned long	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

static void				sh_set_header_properties(t_term *term)
{
	term->header.display_length = 0;
	term->header.unicode_length = 0;
	while (term->header.content[term->header.unicode_length])
	{
		if (term->header.content[term->header.unicode_length] >= 0b11000000
		|| term->header.content[term->header.unicode_length] < 0b10000000)
			term->header.display_length++;
		term->header.unicode_length++;
	}
	term->header.display_length++;
	term->header.unicode_length++;
	term->header.display_length_mod = term->header.display_length % term->window.width;
}

void					term_set_header(t_shell *shell, t_term *term,
							unsigned char *location)
{
	size_t	length;
	size_t	counter;

	if (!location)
		return ;
	(term->header.content) ? ft_strdel((char **)&term->header.content) : 0;
	(term->header.location) ? ft_strdel((char **)&term->header.location) : 0;
	length = ft_strlens((char *)location);
	term->header.location = (unsigned char *)ft_strdups((char *)location);
	if (length == 0)
		term->header.content = NULL;
	else if (ft_strcmps((char *)location, env_search(shell->env, "HOME")) == 0)
		term->header.content = (unsigned char *)ft_strdup("~");
	else if (length == 1 && location[0] == '/')
		term->header.content = (unsigned char *)ft_strdup("~");
	else
	{
		(location[length - 1] == '/') ? location[length--] = '\0' : 0;
		counter = sh_count_slash(location);
		term->header.content = (location[0] == '/' && counter == 1)
			? (unsigned char *)ft_strdup((char *)location)
			: sh_get_folder_name(location, length - 1);
	}
	sh_set_header_properties(term);
}
