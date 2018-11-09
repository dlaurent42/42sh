/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:01:39 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 16:36:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		str2_sizes(char **argv)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (argv[i])
	{
		ret += ft_strlen(argv[i]);
		if (argv[i + 1])
			ret++;
		i++;
	}
	return (ret);
}

static char		*ft_str2tostr(char **argv)
{
	int		i;
	int		x;
	int		cursor;
	char	*ret;

	if (!(ret = ft_strnew(str2_sizes(argv))))
		return (NULL);
	i = 0;
	cursor = 0;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
			ret[cursor++] = argv[i][x++];
		(argv[i + 1]) ? ret[cursor++] = ' ' : (0);
		i++;
	}
	return (ret);
}

t_job			*job_new(int muted, char **argv)
{
	t_job		*job;

	if (!(job = (t_job *)ft_memalloc(sizeof(t_job))))
		return (NULL);
	job->fd[0] = STDIN_FILENO;
	job->fd[1] = STDOUT_FILENO;
	job->fd[2] = STDERR_FILENO;
	job->notifications = muted;
	job->command = ft_str2tostr(argv);
	job->id = 1;
	job->rank = 2;
	job->next = NULL;
	return (job);
}
