/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:43:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			parse_args(t_ac *ac, char **argv)
{
	t_args			*args;
	t_args			*last_args;

	last_args = NULL;
	argv++;
	if (!(args = auto_create_args()))
		return (false);
	if (!(auto_path(args, ".", *argv)))
	{
		free(args);
		return (false);
	}
	if (!ac->args)
		ac->args = args;
	else if (last_args)
		last_args->next = args;
	last_args = args;
	return (true);
}

static bool			get_binaries(t_ac *ac, char **argv)
{
	t_args			*args;
	t_args			*last_args;
	t_bin_auto		*bin_auto;

	last_args = NULL;
	bin_auto = ac->shell->bin->bin_auto;
	if (*argv)
		argv++;
	while (bin_auto)
	{
		if (!(args = auto_create_args()))
			return (false);
		if (!(args->data.str = ft_strdups(bin_auto->name)))
		{
			free(args);
			return (false);
		}
		if (!ac->args)
			ac->args = args;
		else if (last_args)
			last_args->next = args;
		last_args = args;
		bin_auto = bin_auto->next;
	}
	return (true);
}

bool				auto_get_args(t_ac *ac)
{
	if (ac->auto_mode != AUTO_NON && ac->auto_mode != AUTO_BIN)
	{
		if (!(parse_args(ac, ac->argv)))
			return (false);
	}
	else if (ac->auto_mode == AUTO_BIN)
	{
		if (!(get_binaries(ac, ac->argv)))
			return (false);
	}
	return (true);
}
