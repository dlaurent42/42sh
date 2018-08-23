/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 03:05:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 14:25:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf(const char *format, ...)
{
	t_arg	*args;
	va_list	ap;
	char	*str;
	int		len;

	args = NULL;
	str = NULL;
	len = 0;
	va_start(ap, format);
	if (!(args = parse(ap, args, (char *)format)))
		return (-1);
	va_end(ap);
	len = concatenate_content(args->first);
	return (len);
}
