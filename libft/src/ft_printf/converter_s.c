/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/24 22:00:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*lower_s_to_a(va_list ap, t_arg *args)
{
	char	*tmp;

	tmp = NULL;
	if (args->size == S_L)
		return (upper_s_to_a(ap, args));
	tmp = va_arg(ap, char *);
	args->type = T_STRING;
	if (!tmp)
		args->content = ft_strdup("(null)");
	else
		args->content = ft_strdups(tmp);
	return (s_width_flag_precision(args));
}

t_arg	*upper_s_to_a(va_list ap, t_arg *args)
{
	size_t	i;
	wchar_t	*wstr;

	i = 0;
	args->type = T_WSTRING;
	wstr = va_arg(ap, wchar_t *);
	args->content = ft_strdup("");
	if (!wstr)
	{
		ft_strdel(&(args->content));
		args->content = ft_strdup("(null)");
	}
	else
	{
		while (wstr[i])
		{
			args->content = ft_strjoinf(args->content,
			convert_wchar(wstr[i], args), 3);
			i++;
		}
	}
	wstr = NULL;
	return (s_width_flag_precision(args));
}
