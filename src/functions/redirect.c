/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/01 09:46:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	run_cd_cmd(t_shell *sh)
{
	int		i;
	char	res;
	char	**options;

	i = 3;
	options = ft_memalloc(sizeof(char *) * 3);
	options[0] = NULL;
	options[1] = NULL;
	if (sh->buffer.content[3] == '-' && sh->buffer.content[4] == 'L')
	{
		i += 3;
		options[0] = ft_strdups("-L");
	}
	if (sh->buffer.content[3] == '-' && sh->buffer.content[4] == 'P')
	{
		i += 3;
		options[0] = ft_strdups("-P");
	}
	if (sh->buffer.content[6] == '-' && sh->buffer.content[7] == 'L')
	{
		i += 3;
		options[1] = ft_strdups("-L");
	}
	if (sh->buffer.content[6] == '-' && sh->buffer.content[7] == 'P')
	{
		i += 3;
		options[1] = ft_strdups("-P");
	}
	res = sh_cd(sh, sh->buffer.content + i, options);
	ft_strdel(&options[0]);
	ft_strdel(&options[1]);
	ft_memdel((void **)&options);
	return (res);
}

static char	sh_command_dispatcher(t_shell *sh)
{
	char	res;

	res = 0;
	if (sh->buffer.content[0] == 'c' && sh->buffer.content[1] == 'd')
		res = run_cd_cmd(sh);
	else if (sh->buffer.content[0] == 'e' && sh->buffer.content[1] == 'x'
	&& sh->buffer.content[2] == 'i' && sh->buffer.content[3] == 't')
		sh_exit(sh, sh->buffer.content + 5);
	return (res);
}

static void	sh_reset_sh(t_shell *sh)
{
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.cmd = NULL;
	sh->read->unicode_bytes_left = 0;
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	sh_set_prompt(sh);
	sh_print_prompt(sh);
}

void		sh_command_run(t_shell *sh)
{
	sh_move_end(sh);
	ft_putchar('\n');
	sh->prompt.last_exec_succeed = (sh->buffer.display_len)
		? sh_command_dispatcher(sh) : 0;
	(sh->buffer.display_len) ? command_add(sh) : 0;
	sh_reset_sh(sh);
}
