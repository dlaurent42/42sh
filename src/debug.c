/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:31:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/14 20:09:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_debug(t_shell *shell, char *msg, unsigned char *str)
{
	int	i;
	int	fd;

	i = 0;
	fd = open("/dev/ttys003", O_RDWR);
	ft_putendl_fd("", fd);
	if (str)
		while (str[i])
		{
			ft_putstr_fd("[ ", fd);
			ft_putchar_fd(str[i], fd);
			ft_putstr_fd(" | ", fd);
			ft_putnbr_fd(str[i], fd);
			ft_putstr_fd(" ]", fd);
			i++;
		}
	if (msg)
		ft_putstr_fd(msg, fd);
	if (shell)
	{
		ft_putstr_fd("\ncursor\n\tx: ", fd);
		ft_putnbr_fd(shell->term->cursor.x, fd);
		ft_putstr_fd("\ty: ", fd);
		ft_putnbr_fd(shell->term->cursor.y, fd);
		ft_putstr_fd("\tabs_pos: ", fd);
		ft_putnbr_fd(shell->term->cursor.abs_pos, fd);
		ft_putstr_fd("\trel_pos: ", fd);
		ft_putnbr_fd(shell->term->cursor.rel_pos, fd);
		ft_putstr_fd("\nbuffer\n\tdisplay_length: ", fd);
		ft_putnbr_fd(shell->read->buffer.display_length, fd);
		ft_putstr_fd("\tunicode_length: ", fd);
		ft_putnbr_fd(shell->read->buffer.unicode_length, fd);
		ft_putstr_fd("\tcontent: ", fd);
		ft_putstr_fd((char *)shell->read->buffer.content, fd);
		ft_putstr_fd("\nheader\n\tunicode_length: ", fd);
		ft_putnbr_fd(shell->term->header.unicode_length, fd);
		ft_putstr_fd("\tdisplay_length: ", fd);
		ft_putnbr_fd(shell->term->header.display_length, fd);
		ft_putstr_fd("\tdisplay_length_mod: ", fd);
		ft_putnbr_fd(shell->term->header.display_length_mod, fd);
		ft_putstr_fd("\nterm->window\n\twidth: ", fd);
		ft_putnbr_fd(shell->term->window.width, fd);
		ft_putstr_fd("\theight: ", fd);
		ft_putnbr_fd(shell->term->window.height, fd);
		ft_putstr_fd("\tscroll_x: ", fd);
		ft_putnbr_fd(shell->term->window.scroll_x, fd);
		ft_putstr_fd("\tscroll_y: ", fd);
		ft_putnbr_fd(shell->term->window.scroll_y, fd);
	}
	ft_putstr_fd("\n-----------------", fd);
	close(fd);
}
