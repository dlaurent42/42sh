/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:31:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 16:05:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_debug3(t_shell *sh, int fd)
{
	ft_putstr_fd("\tcontent: ", fd);
	ft_putstr_fd((char *)sh->buffer.content, fd);
	ft_putstr_fd("\tstored: ", fd);
	ft_putstr_fd((char *)sh->buffer.stored, fd);
	ft_putstr_fd("\nprompt\n\tdisplay_len: ", fd);
	ft_putnbr_fd(sh->prompt.len, fd);
	ft_putstr_fd("\tdisplay_len_mod: ", fd);
	ft_putnbr_fd(sh->prompt.len_mod, fd);
	ft_putstr_fd("\nwindow\n\twidth: ", fd);
	ft_putnbr_fd(sh->window.width, fd);
	ft_putstr_fd("\theight: ", fd);
	ft_putnbr_fd(sh->window.height, fd);
}

static void	sh_debug2(t_shell *sh, int fd)
{
	ft_putstr_fd("\nmodes\n\tac: ", fd);
	ft_putnbr_fd(sh->modes.auto_completion, fd);
	ft_putstr_fd("\tselect: ", fd);
	ft_putnbr_fd(sh->modes.select, fd);
	ft_putstr_fd("\tbrowse: ", fd);
	ft_putnbr_fd(sh->modes.browse, fd);
	ft_putstr_fd("\ncursor\n\tx: ", fd);
	ft_putnbr_fd(sh->cursor.x, fd);
	ft_putstr_fd("\ty: ", fd);
	ft_putnbr_fd(sh->cursor.y, fd);
	ft_putstr_fd("\tabs_pos: ", fd);
	ft_putnbr_fd(sh->cursor.abs_pos, fd);
	ft_putstr_fd("\trel_pos: ", fd);
	ft_putnbr_fd(sh->cursor.rel_pos, fd);
	ft_putstr_fd("\nbuffer\n\tdisplay_len: ", fd);
	ft_putnbr_fd(sh->buffer.display_len, fd);
	ft_putstr_fd("\tunicode_len: ", fd);
	ft_putnbr_fd(sh->buffer.unicode_len, fd);
	sh_debug3(sh, fd);
}

void		sh_debug(t_shell *sh, char *msg, char *str)
{
	int	i;
	int	fd;

	i = 0;
	fd = open("/dev/ttys002", O_RDWR);
	ft_putendl_fd("", fd);
	if (str)
		while (str[i])
		{
			ft_putstr_fd("[ ", fd);
			ft_putchar_fd((unsigned char)str[i], fd);
			ft_putstr_fd(" | ", fd);
			ft_putnbr_fd((unsigned char)str[i], fd);
			ft_putstr_fd(" ]", fd);
			i++;
		}
	if (msg)
		ft_putstr_fd(msg, fd);
	if (sh)
		sh_debug2(sh, fd);
	ft_putstr_fd("\n-----------------", fd);
	close(fd);
}
