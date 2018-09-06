/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:31:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/06 15:39:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_debug(t_shell *shell, char *msg)
{
	int		fd;

	fd = open("/dev/ttys003", O_RDWR);
	ft_putendl_fd("", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(":\t{x: ", fd);
	ft_putnbr_fd(shell->term->cursor.x, fd);
	ft_putstr_fd(", y: ", fd);
	ft_putnbr_fd(shell->term->cursor.y, fd);
	ft_putstr_fd(", abs: ", fd);
	ft_putnbr_fd(shell->term->cursor.abs_pos, fd);
	ft_putstr_fd(", buff_len: ", fd);
	ft_putnbr_fd(shell->read->buffer.length, fd);
	ft_putstr_fd(", head_len: ", fd);
	ft_putnbr_fd(shell->term->header.length, fd);
	ft_putstr_fd(", window width: ", fd);
	ft_putnbr_fd(shell->term->w_width, fd);
	ft_putstr_fd(", buffer: ", fd);
	ft_putstr_fd(shell->read->buffer.content, fd);
	ft_putstr_fd("}\n-----------------", fd);
	(void)shell;
	close(fd);
}
