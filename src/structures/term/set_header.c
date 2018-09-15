/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 20:21:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 15:08:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//▸

#include "minishell.h"

static void	sh_set_header_properties(t_term *term)
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

void		term_set_header(t_shell *shell, t_term *term, unsigned char *location)
{
	size_t	length;

	(term->header.content) ? ft_strdel((char **)&term->header.content) : 0;
	(term->header.location) ? ft_strdel((char **)&term->header.location) : 0;
	term->header.location = (unsigned char *)ft_strdups((char *)location);
	if ((length = ft_strlens((char *)location)) == 0)
		return ;
	else if (ft_strcmps((char *)location, env_search(shell->env, "HOME")) == 0)
		term->header.content = (unsigned char *)ft_strdup("~");
	else if (length == 1 && location[0] == '/')
		term->header.content = (unsigned char *)ft_strdup("/");
	else
	{
		(location[length - 1] == '/') ? location[length--] = '\0' : 0;
		if ((location[0] == '/' && ft_strcountif((char *)location, '/') == 1))
			term->header.content = (unsigned char *)ft_strdup((char *)location);
		else
		{
			length--;
			while (location[length] && location[length] != '/')
				length--;
			term->header.content = (unsigned char *)ft_strdups((char *)(location + length + 1));
		}
	}
	sh_set_header_properties(term);
}
