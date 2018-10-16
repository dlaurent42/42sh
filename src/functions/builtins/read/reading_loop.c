/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 11:27:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 14:11:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_read_del_return(char *line, char res)
{
	ft_strdel(&line);
	if (res == -99 || res == 0)
		return (0);
	return (res);
}

static char	sh_read_processing(t_env *env, int *opt, char **vars, char **line)
{
	char	buffer[2];

	ft_bzero((void *)buffer, sizeof(char) * 2);
	if ((read(opt[READ_U], (void *)buffer, READ_SIZE)) != READ_SIZE)
		return (1);
	if (buffer[0] == 4)
		return (1);
	if (buffer[0] == opt[READ_D] || (opt[READ_N] != -1 && --opt[READ_N] == 0))
	{
		(opt[READ_E] == 0) ? ft_putendl(*line) : 0;
		return (sh_read_set(env, vars, sh_read_parse_line(*line, opt[READ_R])));
	}
	if (ft_isprint(buffer[0]))
		*line = ft_strjoinf(*line, buffer, 1);
	if (opt[READ_S] == -1 && ft_isprint(buffer[0]))
		ft_putchar(buffer[0]);
	return (0);
}

char		sh_read_loop(t_shell *sh, t_env *env, int *opt, char **vars)
{
	char	res;
	char	*line;
	fd_set	r_fd;

	(void)sh;
	FD_ZERO(&r_fd);
	FD_SET(opt[READ_U], &r_fd);
	res = 0;
	line = NULL;
	while (TRUE)
		if ((res = select(opt[READ_U] + 1, &r_fd, NULL, NULL, NULL)) > 0)
		{
			if ((res = sh_read_processing(env, opt, vars, &line)) != 0)
				return (sh_read_del_return(line, res));
		}
		else
			return (sh_read_del_return(line, 1));
	return (sh_read_del_return(line, res));
}

char		sh_read_timeout_loop(t_shell *sh, t_env *env, int *opt, char **vars)
{
	char			res;
	char			*line;
	unsigned long	timer;
	fd_set			r_fd;
	t_timeval		timeout;

	(void)sh;
	FD_ZERO(&r_fd);
	FD_SET(opt[READ_U], &r_fd);
	res = 0;
	line = NULL;
	timer = (unsigned long)time(NULL) + opt[READ_T];
	timeout.tv_usec = 0;
	while ((timeout.tv_sec = timer - (unsigned long)time(NULL)) > 0)
		if ((res = select(opt[READ_U] + 1, &r_fd, NULL, NULL, &timeout)) > 0)
		{
			if ((res = sh_read_processing(env, opt, vars, &line)) != 0)
				return (sh_read_del_return(line, res));
		}
		else
			return (sh_read_del_return(line, 1));
	return (sh_read_del_return(line, res));
}
