/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 21:26:35 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	get_number(int ttyfd, unsigned int *ret, char c)
{
	char	buffer[2];

	ft_bzero(buffer, 2);
	*ret = 0;
	if (read(ttyfd, buffer, 1) < 1)
		return (FALSE);
	while (buffer[0] >= '0' && buffer[0] <= '9')
	{
		*ret = 10 * (*ret) + buffer[0] - '0';
		if (read(ttyfd, buffer, 1) < 1)
			return (FALSE);
	}
	return (buffer[0] == c);
}

static bool	verify_buf(int ttyfd, char *str)
{
	char	buffer[2];
	int		i;

	ft_bzero(buffer, 2);
	if (str)
	{
		i = 0;
		if (read(ttyfd, buffer, 1) < 1)
			return (FALSE);
		while (str[i] && str[i + 1])
		{
			if (str[i] != buffer[0])
				return (FALSE);
			i++;
			if (!(str[i]))
				break ;
			if (read(ttyfd, buffer, 1) < 1)
				return (FALSE);
		}
	}
	return (TRUE);
}

static void	sh_last_char(t_shell *sh)
{
	t_termios	term[2];
	int			ttyfd;

	if ((ttyfd = dup(0)) < 1)
		return ;
	if (tcgetattr(ttyfd, &term[0]) < 0 || tcgetattr(ttyfd, &term[1]) < 0)
		return ;
	term[1].c_lflag &= ~ICANON;
	term[1].c_lflag &= ~ECHO;
	term[1].c_cflag &= ~CREAD;
	tcsetattr(ttyfd, TCSANOW, &term[1]);
	write(ttyfd, "\033[6n", 4);
	if (!verify_buf(ttyfd, (char[3]){27, '[', 0}))
		return ;
	if (!get_number(ttyfd, (unsigned int *)&sh->cursor.y, ';'))
		return ;
	if (!get_number(ttyfd, (unsigned int *)&sh->cursor.x, 'R'))
		return ;
	sh->cursor.y--;
	sh->cursor.x--;
	tcsetattr(ttyfd, TCSANOW, &term[0]);
	(sh->cursor.x) ? ft_putendl(COL_WHIGHLIGHT"%"COL_CLR) : 0;
	close(ttyfd);
}

static void	sh_reset_sh(t_shell *sh)
{
	bool	subshell;

	subshell = sh->modes.subshell;
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len + sh->buffer.ushift);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.dshift = 0;
	sh->buffer.ushift = 0;
	sh->buffer.cmd = NULL;
	sh->read->unicode_bytes_left = 0;
	sh->pid = 0;
	sh->jc_muted = 0;
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	(sh->jc) ? job_notification() : (0);
	(!subshell) ? sh_set_prompt(sh) : 0;
	(!subshell) ? sh_print_prompt(sh) : 0;
	sh->modes.subshell = (subshell) ? 2 : 0;
}

void		sh_command_prepare(t_shell *sh)
{
	char	status;

	status = 0;
	g_exit_code = 0;
	(!sh->modes.subshell || (sh->modes.subshell && sh->modes.multiline))
		? sh_move_end(sh) : 0;
	(!sh->modes.subshell || sh->modes.multiline) ? ft_putchar('\n') : 0;
	if (!(sh->buffer.parsed = ft_strdups(sh->buffer.content)))
		sh->buffer.parsed = ft_strdups("");
	if ((status = sh_command_run(sh, sh->env, sh->bin, &sh->buffer.parsed)) > 0
	&& status < STATUS_PERMISSION_DENIED)
		return (sh_multilines(sh, status));
	else if (status == STATUS_ERR && sh && sh->env
	&& (env_search(sh->env, "?") || (!env_search(sh->env, "?")
	&& sh->env->count + 1 < sh->env->size)))
		env_insert_protected(sh, sh->env, "?", "1");
	ft_strdel(&sh->buffer.parsed);
	(!sh->modes.subshell) ? sh_last_char(sh) : 0;
	sh_reset_sh(sh);
}
