/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 01:51:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/06/28 21:52:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*manage_prefix(t_arg **args)
{
	size_t	i;

	i = 0;
	if ((*args)->content && (*args)->content[0] == '-')
	{
		while ((*args)->content[i])
		{
			(*args)->content[i] = (*args)->content[i + 1];
			i++;
		}
		return (ft_strdup("-"));
	}
	if ((*args)->flag && (*args)->flag[F_PLUS])
		return (ft_strdup("+"));
	if ((*args)->flag && (*args)->flag[F_SPACE])
		return (ft_strdup(" "));
	return (NULL);
}

static t_arg	*manipulate_precision(t_arg *args)
{
	int		size;
	char	*tmp;

	tmp = NULL;
	size = (int)ft_strlens(args->content);
	if (args->content && args->content[0] == '0' && args->precision > 0)
	{
		tmp = ft_strnew(sizeof(char) * args->precision);
		tmp = (char *)ft_memsets((void *)tmp, '0', args->precision);
		ft_strdel(&(args->content));
		args->content = ft_strdups(tmp);
	}
	else if (args->content && args->content[0] == '0' && args->precision == 0)
	{
		ft_strdel(&(args->content));
		args->content = ft_strdup("");
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

static t_arg	*manipulate_width_o(t_arg *args, char *prefix)
{
	int		size;
	char	*tmp;

	size = (int)(ft_strlens(args->content) + ft_strlens(prefix));
	tmp = ft_strnew(sizeof(char) * (args->min_width - size - 1));
	tmp = (char *)ft_memsets((void *)tmp, '0', args->min_width - size - 1);
	args->content = ft_strjoinf(tmp, args->content, 2);
	args->content = ft_strjoinf(prefix, args->content, 2);
	ft_strdel(&tmp);
	return (args);
}

static t_arg	*manipulate_width_no(t_arg *args, char *prefix)
{
	int		size;
	char	*tmp;

	size = (int)(ft_strlens(args->content) + ft_strlens(prefix));
	tmp = ft_strnew(sizeof(char) * (args->min_width - size - 1));
	tmp = (char *)ft_memsets((void *)tmp, ' ', args->min_width - size - 1);
	if (args->flag && args->flag[F_DASH])
	{
		args->content = ft_strjoinf(prefix, args->content, 2);
		args->content = ft_strjoinf(args->content, tmp, 1);
	}
	else
	{
		args->content = ft_strjoinf(prefix, args->content, 2);
		args->content = ft_strjoinf(tmp, args->content, 2);
	}
	ft_strdel(&tmp);
	return (args);
}

t_arg			*id_width_flag_precision(t_arg *args)
{
	char	*prefix;

	prefix = manage_prefix(&args);
	if (args->precision != -1
	&& (args->precision > (int)ft_strlens(args->content)
	|| (args->content && args->content[0] == '0')))
		args = manipulate_precision(args);
	if (args->min_width != -1
	&& args->min_width > (int)(ft_strlens(args->content) + ft_strlens(prefix)))
	{
		if (args->flag
		&& args->flag[F_ZERO] && !args->flag[F_DASH] && args->precision == -1)
			args = manipulate_width_o(args, prefix);
		else
			args = manipulate_width_no(args, prefix);
	}
	else
		args->content = ft_strjoinf(prefix, args->content, 2);
	ft_strdel(&prefix);
	return (args);
}
