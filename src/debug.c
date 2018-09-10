/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:31:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/10 21:41:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_debug2(t_shell *shell)
{
	int					fd;
	unsigned int		i;

	i = 0;
	fd = open("/dev/ttys04", O_RDWR);
	while (i < shell->read->buffer.unicode_length)
	{
		ft_putendl_fd("", fd);
		ft_putnbr_fd((char)shell->read->buffer.content[i], fd);
		ft_putstr_fd(" [", fd);
		ft_putchar_fd((char)shell->read->buffer.content[i], fd);
		ft_putendl_fd("]", fd);
		i++;
	}
	ft_putstr_fd("\n-----------------", fd);
	close(fd);
}

void	sh_debug(t_shell *shell, char *msg)
{
	int		i;
	int		fd;

	i = 0;
	fd = open("/dev/ttys000", O_RDWR);
	ft_putendl_fd("", fd);
	if (msg)
		ft_putstr_fd(msg, fd);
	if (shell)
	{
		ft_putstr_fd("\n\tcursor.x: ", fd);
		ft_putnbr_fd(shell->term->cursor.x, fd);
		ft_putstr_fd("\n\tcursor.y: ", fd);
		ft_putnbr_fd(shell->term->cursor.y, fd);
		ft_putstr_fd("\n\tcursor.abs_pos: ", fd);
		ft_putnbr_fd(shell->term->cursor.abs_pos, fd);
		ft_putstr_fd("\n\tcursor.rel_pos: ", fd);
		ft_putnbr_fd(shell->term->cursor.rel_pos, fd);
		ft_putstr_fd("\n\tbuffer.display_length: ", fd);
		ft_putnbr_fd(shell->read->buffer.display_length, fd);
		ft_putstr_fd("\n\tbuffer.unicode_length: ", fd);
		ft_putnbr_fd(shell->read->buffer.unicode_length, fd);
		ft_putstr_fd("\n\tbuffer.content: ", fd);
		ft_putstr_fd((char *)shell->read->buffer.content, fd);
		ft_putstr_fd("\n\t[", fd);
		while (shell->read->buffer.content[i])
		{
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(shell->read->buffer.content[i], fd);
			ft_putstr_fd(" ", fd);
			i++;
		}
		ft_putstr_fd("]\n\theader.unicode_length: ", fd);
		ft_putnbr_fd(shell->term->header.unicode_length, fd);
		ft_putstr_fd("\n\theader.display_length: ", fd);
		ft_putnbr_fd(shell->term->header.display_length, fd);
		ft_putstr_fd("\n\theader.display_length_mod: ", fd);
		ft_putnbr_fd(shell->term->header.display_length_mod, fd);
		ft_putstr_fd("\n\tterm->w_width: ", fd);
		ft_putnbr_fd(shell->term->w_width, fd);
	}
	ft_putstr_fd("\n-----------------", fd);
	close(fd);
	if (shell)
		sh_debug2(shell);
}
