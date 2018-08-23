/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:51:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 14:30:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*handlers(va_list ap, t_arg *args, char **fmt)
{
	args = handle_flags(args, fmt);
	args = handle_min_width(ap, args, fmt);
	args = handle_precision(ap, args, fmt);
	args = handle_size(args, fmt);
	args = handle_conversion(ap, args, fmt);
	return (args);
}

t_arg	*parse(va_list ap, t_arg *args, char *fmt)
{
	size_t	len;

	len = ft_strlens(fmt) - ft_strlens(ft_strchrs(fmt, '%'));
	if (!(args = add_node(args)))
		return (error_handler_with_ap(ap, args));
	if (!fmt)
		args->content = ft_strdup("");
	else if (!(ft_strchr(fmt, '%')))
		args->content = ft_strdups(fmt);
	if (!fmt || !(ft_strchr(fmt, '%')))
		return (args->first);
	else if (len > 0)
	{
		if (!(args->content = ft_strnew(sizeof(char) * len)))
			return (args);
		args->content = ft_strncpys(args->content, fmt, len);
		return (parse(ap, args, ft_strchr(fmt, '%')));
	}
	else
	{
		fmt++;
		args = handlers(ap, args, &fmt);
		return (parse(ap, args, fmt));
	}
}
