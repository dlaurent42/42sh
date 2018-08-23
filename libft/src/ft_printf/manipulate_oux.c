/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_oux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:51:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/06/28 21:54:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_arg	*manipulate_hashtag(t_arg *args)
{
	if (!(args->content) || (args->flag
	&& args->flag[F_ZERO] && !args->flag[F_DASH] && args->precision == -1))
		return (args);
	if (args->content[0] != '0'
	&& (args->type == T_UNSIGNED_OCTAL
	|| args->type == T_LONG_UNSIGNED_OCTAL))
		args->content = ft_strjoinf("0", args->content, 2);
	else if (args->type == T_HEXA)
		args->content = ft_strjoinf("0x", args->content, 2);
	else if (args->type == T_LONG_HEXA)
		args->content = ft_strjoinf("0X", args->content, 2);
	return (args);
}

static t_arg	*manipulate_precision(t_arg *args, int is_zero)
{
	int		size;
	char	*tmp;

	tmp = NULL;
	size = (int)ft_strlens(args->content);
	if (is_zero)
	{
		tmp = ft_strnew(sizeof(char) * args->precision);
		tmp = (char *)ft_memsets((void *)tmp, '0', args->precision);
		ft_strdel(&(args->content));
		args->content = ft_strdups(tmp);
	}
	else
	{
		tmp = ft_strnew(sizeof(char) * (args->precision - size));
		tmp = (char *)ft_memsets((void *)tmp, '0', args->precision - size);
		args->content = ft_strjoinf(tmp, args->content, 2);
	}
	ft_strdel(&tmp);
	return (args);
}

static t_arg	*manipulate_width_o(t_arg *args, int is_zero)
{
	int		size;
	char	*tmp;

	size = (int)ft_strlens(args->content);
	tmp = ft_strnew(sizeof(char) * (args->min_width - size - 1));
	tmp = (char *)ft_memsets((void *)tmp, '0', args->min_width - size - 1);
	args->content = ft_strjoinf(tmp, args->content, 2);
	if (args->flag && args->flag[F_HASHTAG])
	{
		if (args->content && args->type == T_HEXA && !is_zero)
			args->content[1] = 'x';
		else if (args->content && args->type == T_LONG_HEXA && !is_zero)
			args->content[1] = 'X';
	}
	ft_strdel(&tmp);
	return (args);
}

static t_arg	*manipulate_width_no(t_arg *args)
{
	int		size;
	char	*tmp;

	size = (int)ft_strlens(args->content);
	tmp = ft_strnew(sizeof(char) * (args->min_width - size - 1));
	tmp = (char *)ft_memsets((void *)tmp, ' ', args->min_width - size - 1);
	if (args->flag && args->flag[F_DASH])
		args->content = ft_strjoinf(args->content, tmp, 1);
	else
		args->content = ft_strjoinf(tmp, args->content, 2);
	ft_strdel(&tmp);
	return (args);
}

t_arg			*oux_width_flag_precision(t_arg *args)
{
	int		is_zero;

	if (args->content && args->content[0] == '0')
		is_zero = 1;
	else
		is_zero = 0;
	if (args->precision != -1
	&& (args->precision > (int)ft_strlens(args->content) || is_zero))
		args = manipulate_precision(args, is_zero);
	if (args->flag && args->flag[F_HASHTAG] && !is_zero)
		args = manipulate_hashtag(args);
	else if (args->flag && args->flag[F_HASHTAG] && is_zero
	&& args->precision == 0
	&& (args->type == T_UNSIGNED_OCTAL || args->type == T_LONG_UNSIGNED_OCTAL))
		args->content = ft_strjoinf("0", args->content, 2);
	if (args->min_width != -1
	&& args->min_width > (int)ft_strlens(args->content))
	{
		if (args->flag
		&& args->flag[F_ZERO] && !args->flag[F_DASH] && args->precision == -1)
			args = manipulate_width_o(args, is_zero);
		else
			args = manipulate_width_no(args);
	}
	return (args);
}
