/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:49:45 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 14:44:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_arg	*null_char(t_arg *args)
{
	if (args->min_width == -1)
	{
		args->len = 1;
		if (!(args->content = ft_strnew(sizeof(char))))
			return (NULL);
		args->content[0] = 0;
	}
	else
	{
		if (!(args->content = ft_strnew(sizeof(char) * (args->min_width - 1))))
			return (NULL);
		args->content =
		(char *)ft_memsets((void *)args->content, ' ', args->min_width - 1);
		if (args->flag && args->flag[F_DASH])
			args->content[0] = 0;
		else
			args->content[args->min_width - 2] = 0;
		args->len = args->min_width - 1;
	}
	return (args);
}

t_arg			*lower_c_to_a(va_list ap, t_arg *args)
{
	char	c;
	char	*tmp;

	tmp = NULL;
	if (args->size == S_L)
		return (upper_c_to_a(ap, args));
	args->type = T_CHAR;
	c = (char)va_arg(ap, int);
	if (c == 0)
		return (null_char(args));
	if ((args->content = ft_strnew(sizeof(char))))
		args->content[0] = c;
	args->len = 1;
	if (args->min_width != -1)
	{
		tmp = ft_strnew(sizeof(char) * (args->min_width - 2));
		tmp =
		(char *)ft_memsets((void *)tmp, ' ', args->min_width - 2);
		if (args->flag && args->flag[F_DASH])
			args->content = ft_strjoinf(args->content, tmp, 3);
		else
			args->content = ft_strjoinf(tmp, args->content, 3);
		args->len = args->min_width - 1;
	}
	return (args);
}

t_arg			*upper_c_to_a(va_list ap, t_arg *args)
{
	wchar_t	c;
	char	*tmp;

	args->type = T_WCHAR;
	c = va_arg(ap, wchar_t);
	tmp = NULL;
	if (c == 0)
	{
		args->len = 1;
		return (null_char(args));
	}
	args->content = convert_wchar(c, args);
	if (args->min_width != -1)
	{
		tmp = ft_strnew(sizeof(char) * (args->min_width - args->len - 1));
		tmp =
		(char *)ft_memsets((void *)tmp, ' ', args->min_width - args->len - 1);
		if (args->flag && args->flag[F_DASH])
			args->content = ft_strjoinf(args->content, tmp, 3);
		else
			args->content = ft_strjoinf(tmp, args->content, 3);
		args->len = 0;
	}
	return (args);
}
