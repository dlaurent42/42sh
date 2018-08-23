/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 13:55:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/02 03:54:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_read	*add_reader(int const fd, t_read *current_reader)
{
	t_read	*reader;

	reader = NULL;
	if (!(reader = (t_read *)malloc(sizeof(t_read))))
		return (NULL);
	reader->fd = fd;
	reader->rr = 1;
	reader->gnl = -1;
	reader->content = NULL;
	reader->head = NULL;
	reader->next = NULL;
	if (current_reader)
	{
		current_reader->next = reader;
		reader->head = current_reader->head;
	}
	else
		reader->head = reader;
	return (reader);
}

static	t_read	*fd_already_stored(int const fd, t_read *reader)
{
	if (!reader)
		return (add_reader(fd, reader));
	reader = reader->head;
	while (reader->next && reader->fd != fd)
		reader = reader->next;
	if (reader->fd == fd)
		return (reader);
	else
		return (add_reader(fd, reader));
}

static int		handle_reader(t_read **reader)
{
	t_read	*tmp;

	if ((*reader)->gnl != 0 || (*reader)->fd > 2)
		return ((*reader)->gnl);
	if (*reader == (*reader)->head)
	{
		tmp = (*reader)->next;
		while (tmp)
		{
			tmp->head = (*reader)->next;
			tmp = tmp->next;
		}
	}
	else
	{
		tmp = (*reader)->head;
		while (tmp)
		{
			if (tmp->next == (*reader))
				tmp->next = (*reader)->next;
			tmp = tmp->next;
		}
	}
	free((*reader));
	return (0);
}

static t_read	*manipulate_data(t_read *reader, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchrs(reader->content, '\n'))
	{
		*line = ft_strsub(reader->content, 0, ft_strlens(reader->content)
		- ft_strlens(ft_strchrs(reader->content, '\n')));
		if (!ft_strcmp(ft_strchrs(reader->content, '\n'), "\n"))
			ft_strdel(&(reader->content));
		else
		{
			tmp = ft_strdup(ft_strchrsp(reader->content, '\n'));
			ft_strdel(&(reader->content));
			reader->content = tmp;
		}
		reader->gnl = 1;
	}
	else if (reader->rr >= 0 && reader->rr < BUFF_SIZE)
	{
		if (reader->content[0])
			*line = ft_strdup(reader->content);
		reader->gnl = (reader->content[0] == '\0') ? 0 : 1;
		ft_strdel(&(reader->content));
	}
	return (reader);
}

int				get_next_line(int const fd, char **line)
{
	size_t			reading_ok;
	static t_read	*reader = NULL;

	if (!line || fd < 0 || !(reader = fd_already_stored(fd, reader))
	|| !(reader->buff = ft_strnew(sizeof(char) * BUFF_SIZE)))
		return (-1);
	reading_ok = 1;
	while (reading_ok)
	{
		if ((reader->rr = read(reader->fd, reader->buff, BUFF_SIZE)) == -1)
			return (-1);
		reader->buff[reader->rr] = '\0';
		reader->content = ft_strjoinf(reader->content, reader->buff, 1);
		if (ft_strchrs(reader->content, '\n')
		|| (reader->rr >= 0 && reader->rr < BUFF_SIZE))
		{
			reader = manipulate_data(reader, line);
			reading_ok = 0;
		}
		ft_strclr(reader->buff);
	}
	ft_strdel(&(reader->buff));
	return (handle_reader(&reader));
}
