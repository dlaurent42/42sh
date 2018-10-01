/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:43:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/30 19:26:20 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			parse_args(t_frame *frame, char **argv)
{
	t_args			*args;
	t_args			*last_args;

	last_args = NULL;
	if (*argv)
		argv++;
	if (!*argv)
	{
		if (!(frame->args = auto_create_args()))
			return (false);
		if (!(frame->args->data.str = ft_strdup("."))
				|| !(frame->args->data.path = ft_strdup(".")))
			return (false);
	}
	else
	{
		if (!(args = auto_create_args()))
			return (false);
		if (!(auto_path(args, ".", *argv)))
		{
			free(args);
			return (false);
		}
		if (!frame->args)
			frame->args = args;
		else if (last_args)
			last_args->next = args;
		last_args = args;
	}
	return (true);
}

static bool			get_binaries(t_frame *frame, char **argv)
{
	t_args			*args;
	t_args			*last_args;
	t_bin_auto		*bin_auto;

	last_args = NULL;
	bin_auto = frame->shell->bin->bin_auto;
	if (*argv)
		argv++;
	while (bin_auto)
	{
		if (!(args = auto_create_args()))
			return (false);
		if (!(args->data.str = ft_strdup(bin_auto->name)))
		{
			free(args);
			return (false);
		}
		if (!frame->args)
			frame->args = args;
		else if (last_args)
			last_args->next = args;
		last_args = args;
		bin_auto = bin_auto->next;
	}
	return (true);
}

bool				auto_get_args(t_frame *frame)
{
	if (frame->auto_mode != AUTO_NON && frame->auto_mode != AUTO_BIN)
	{
		if(!(parse_args(frame, frame->argv)))
			return (false);
	}
	else if (frame->auto_mode == AUTO_BIN)
	{
		if(!(get_binaries(frame, frame->argv)))
			return (false);
	}
	return (true);
}
