/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:43:19 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/17 08:44:23 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			parse_args(t_frame *frame, char **argv)
{
	t_args			*args;
	t_args			*last_args;

	if (*argv)
		argv++;
	if (!*argv)
	{
		if (!(frame->args = create_args()))
			error_exit(frame, "Malloc Failed");
		if (!(frame->args->data.str = ft_strdup("."))
				|| !(frame->args->data.path = ft_strdup(".")))
			error_exit(frame, "Malloc Failed");
	}
	while (*argv)
	{
		if (!(args = create_args()))
			error_exit(frame, "Malloc Failed");
		path(frame, args, ".", *argv);
		if (!frame->args)
			frame->args = args;
		else
			last_args->next = args;
		last_args = args;
		argv++;
	}
}

void				get_args(t_frame *frame)
{
	parse_args(frame, frame->argv);
}
