/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 17:37:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_dispatcher(t_shell *sh)
{
	int		i;
	char	res;
	char	**strsplt;

	res = 0;
	strsplt = NULL;

	// ALIAS
	if (sh->buffer.content[0] == 'a' && sh->buffer.content[1] == 'l' && sh->buffer.content[2] == 'i' && sh->buffer.content[3] == 'a' && sh->buffer.content[4] == 's')
	{
		strsplt = ft_strsplit(sh->buffer.content + 6, ' ');
		res = sh_alias(sh, sh->env, strsplt);
	}

	// CD
	else if (sh->buffer.content[0] == 'c' && sh->buffer.content[1] == 'd')
	{
		strsplt = ft_strsplit(sh->buffer.content + 3, ' ');
		res = sh_cd(sh, sh->env, strsplt);
	}
	// ECHO
	else if (sh->buffer.content[0] == 'e' && sh->buffer.content[1] == 'c' && sh->buffer.content[2] == 'h' && sh->buffer.content[3] == 'o')
	{
		strsplt = ft_strsplit(sh->buffer.content + 5, ' ');
		sh_echo(sh, sh->env, strsplt);
	}
	// ENV
	else if (sh->buffer.content[0] == 'e' && sh->buffer.content[1] == 'n' && sh->buffer.content[2] == 'v')
	{
		strsplt = ft_strsplit(sh->buffer.content + 4, ' ');
		res = sh_env(sh, sh->env, strsplt);
	}
	// EXIT
	else if (sh->buffer.content[0] == 'e' && sh->buffer.content[1] == 'x' && sh->buffer.content[2] == 'i' && sh->buffer.content[3] == 't')
	{
		strsplt = ft_strsplit(sh->buffer.content + 5, ' ');
		sh_exit(sh, sh->env, strsplt);
	}
	// EXPORT
	else if (sh->buffer.content[0] == 'e' && sh->buffer.content[1] == 'x' && sh->buffer.content[2] == 'p' && sh->buffer.content[3] == 'o' && sh->buffer.content[4] == 'r' && sh->buffer.content[5] == 't')
	{
		strsplt = ft_strsplit(sh->buffer.content + 7, ' ');
		sh_export(sh, sh->env, strsplt);
	}
	// HISTORY
	else if (sh->buffer.content[0] == 'h' && sh->buffer.content[1] == 'i' && sh->buffer.content[2] == 's' && sh->buffer.content[3] == 't' && sh->buffer.content[4] == 'o' && sh->buffer.content[5] == 'r' && sh->buffer.content[6] == 'y')
	{
		strsplt = ft_strsplit(sh->buffer.content + 8, ' ');
		res = sh_history(sh, sh->env, strsplt);
	}
	// READ
	else if (sh->buffer.content[0] == 'r' && sh->buffer.content[1] == 'e' && sh->buffer.content[2] == 'a' && sh->buffer.content[3] == 'd')
	{
		strsplt = ft_strsplit(sh->buffer.content + 5, ' ');
		res = sh_read_builtin(sh, sh->env, strsplt);
	}
	// SETENV
	else if (sh->buffer.content[0] == 's' && sh->buffer.content[1] == 'e' && sh->buffer.content[2] == 't' && sh->buffer.content[3] == 'e' && sh->buffer.content[4] == 'n' && sh->buffer.content[5] == 'v')
	{
		strsplt = ft_strsplit(sh->buffer.content + 7, ' ');
		res = sh_setenv(sh, sh->env, strsplt);
	}
	// UNALIAS
	else if (sh->buffer.content[0] == 'u' && sh->buffer.content[1] == 'n' && sh->buffer.content[2] == 'a' && sh->buffer.content[3] == 'l' && sh->buffer.content[4] == 'i' && sh->buffer.content[5] == 'a' && sh->buffer.content[6] == 's')
	{
		strsplt = ft_strsplit(sh->buffer.content + 8, ' ');
		res = sh_unalias(sh, sh->env, strsplt);
	}
	// UNSETENV
	else if (sh->buffer.content[0] == 'u' && sh->buffer.content[1] == 'n' && sh->buffer.content[2] == 's' && sh->buffer.content[3] == 'e' && sh->buffer.content[4] == 't' && sh->buffer.content[5] == 'e' && sh->buffer.content[6] == 'n' && sh->buffer.content[7] == 'v')
	{
		strsplt = ft_strsplit(sh->buffer.content + 9, ' ');
		res = sh_unsetenv(sh, sh->env, strsplt);
	}
	// UNSET
	else if (sh->buffer.content[0] == 'u' && sh->buffer.content[1] == 'n' && sh->buffer.content[2] == 's' && sh->buffer.content[3] == 'e' && sh->buffer.content[4] == 't')
	{
		strsplt = ft_strsplit(sh->buffer.content + 6, ' ');
		res = sh_unset(sh, sh->env, strsplt);
	}

	i = 0;
	while (strsplt && strsplt[i])
	{
		ft_strdel(&strsplt[i]);
		i++;
	}
	(strsplt) ? free(strsplt) : 0;
	return (res);
}

static char	sh_command_check(t_shell *sh)
{
	int	i;
	int	count_dquote;
	int	count_squote;

	i = 0;
	count_dquote = 0;
	count_squote = 0;
	while (sh->buffer.content[i])
	{
		count_dquote += (sh->buffer.content[i] == '"') ? 1 : 0;
		count_squote += (sh->buffer.content[i] == '\'') ? 1 : 0;
		i++;
	}
	return (!(count_dquote % 2 || count_squote % 2));
}

static void	sh_reset_sh(t_shell *sh)
{
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.dshift = 0;
	sh->buffer.ushift = 0;
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
	if (sh_command_check(sh) == FALSE)
		return (sh_multilines(sh));
	sh->prompt.last_exec_succeed = (sh->buffer.display_len)
		? sh_command_dispatcher(sh) : 0;
	(sh->buffer.display_len) ? command_add(sh, true) : 0;
	sh_reset_sh(sh);
}
