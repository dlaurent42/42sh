/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:49:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 14:31:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size_of_resulting_string(t_arg *args)
{
	int	size;

	size = 0;
	while (args)
	{
		if (args->content && args->len > 0)
			size += args->len;
		else if (args->content)
			size += (int)ft_strlens(args->content);
		args = args->next;
	}
	return (size);
}

static t_arg	*free_list(t_arg *args)
{
	t_arg	*tmp;

	if (!args)
		return (NULL);
	tmp = args->next;
	ft_strdel(&(args->content));
	free(args->flag);
	free(args);
	return (tmp);
}

int				concatenate_content(t_arg *args)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	len = get_size_of_resulting_string(args);
	if (!(str = ft_strnew(sizeof(char) * len)))
		return (error_handler_without_ap(args));
	while (args)
	{
		j = 0;
		if (args->content && args->len)
			while (j < args->len)
				str[i++] = args->content[j++];
		else if (args->content)
			while (args->content[j])
				str[i++] = args->content[j++];
		args = free_list(args);
	}
	write(1, str, len);
	ft_strdel(&str);
	return (len);
}
