/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:31:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:41:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sh_debug2(t_shell *shell)
// {
// 	int					fd;
// 	unsigned int		i;

// 	i = 0;
// 	fd = open("/dev/ttys08", O_RDWR);
// 	while (i < shell->read->buffer.unicode_length)
// 	{
// 		fprintf(fd, "");
// 		fprintf(fd, (char)shell->read->buffer.content[i]);
// 		fprintf(fd, " [");
// 		ft_putchar_fd(fd, (char)shell->read->buffer.content[i]);
// 		fprintf(fd, "]");
// 		i++;
// 	}
// 	fprintf(fd, "\n-----------------");
// 	close(fd);
// }

void	sh_debug(t_shell *shell, char *msg)
{
	int		i;
	static int	id = 0;
	char	*s;

	s = ft_strjoin("file", ft_itoa(id));
	FILE 	*fd = fopen(s, "w");

	i = 0;
	fprintf(fd, "");
	if (msg)
		fprintf(fd, "%s", msg);
	if (shell)
	{
		fprintf(fd, "\n\tcursor.x: %u", shell->term->cursor.x);
		fprintf(fd, "\n\tcursor.y: %u", shell->term->cursor.y);
		fprintf(fd, "\n\tcursor.abs_pos: %u", shell->term->cursor.abs_pos);
		fprintf(fd, "\n\tcursor.rel_pos: %u", shell->term->cursor.rel_pos);
		fprintf(fd, "\n\tbuffer.display_length: %u", shell->read->buffer.display_length);
		fprintf(fd, "\n\tbuffer.unicode_length: %u", shell->read->buffer.unicode_length);
		fprintf(fd, "\n\tbuffer.content: %s", (char *)shell->read->buffer.content);
		fprintf(fd, "\n\t[");
		while (shell->read->buffer.content[i])
		{
			fprintf(fd, " %c ", shell->read->buffer.content[i]);
			i++;
		}
		fprintf(fd, "]\n\theader.unicode_length: %u", shell->term->header.unicode_length);
		fprintf(fd, "\n\theader.display_length: %u", shell->term->header.display_length);
		fprintf(fd, "\n\theader.display_length_mod: %u", shell->term->header.display_length_mod);
		fprintf(fd, "\n\tterm->w_width: %u", shell->term->w_width);
	}
	fprintf(fd, "\n-----------------");
	fclose(fd);
	free(s);
	i++;
	// if (shell)
	// 	sh_debug2(shell);
}
