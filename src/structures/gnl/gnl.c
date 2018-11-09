/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 13:55:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:25:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_gnl	*add_r(int const fd, t_gnl *current_gnl_r)
{
	t_gnl	*r;

	r = NULL;
	if (!(r = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	r->fd = fd;
	r->rr = 1;
	r->gnl = -1;
	r->content = NULL;
	r->head = NULL;
	r->next = NULL;
	if (current_gnl_r)
	{
		current_gnl_r->next = r;
		r->head = current_gnl_r->head;
	}
	else
		r->head = r;
	return (r);
}

static	t_gnl	*fd_already_stored(int const fd, t_gnl *r)
{
	if (!r)
		return (add_r(fd, r));
	r = r->head;
	while (r->next && r->fd != fd)
		r = r->next;
	if (r->fd == fd)
		return (r);
	return (add_r(fd, r));
}

static int		handle_r(t_gnl **r)
{
	t_gnl	*tmp;

	if ((*r)->gnl != 0 || (*r)->fd > 2)
		return ((*r)->gnl);
	if (*r == (*r)->head)
	{
		tmp = (*r)->next;
		while (tmp)
		{
			tmp->head = (*r)->next;
			tmp = tmp->next;
		}
	}
	else
	{
		tmp = (*r)->head;
		while (tmp)
		{
			if (tmp->next == (*r))
				tmp->next = (*r)->next;
			tmp = tmp->next;
		}
	}
	free(*r);
	return (0);
}

static t_gnl	*manipulate_data(t_gnl *r, char **line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchrs(r->content, '\n'))
	{
		*line = ft_strsub(r->content, 0, ft_strlens(r->content)
		- ft_strlens(ft_strchrs(r->content, '\n')));
		if (!ft_strcmp(ft_strchrs(r->content, '\n'), "\n"))
			ft_strdel(&(r->content));
		else
		{
			tmp = ft_strdup(ft_strchrsp(r->content, '\n'));
			ft_strdel(&(r->content));
			r->content = tmp;
		}
		r->gnl = 1;
	}
	else if (r->rr >= 0 && r->rr < BUFF_SIZE)
	{
		if (r->content[0])
			*line = ft_strdup(r->content);
		r->gnl = (r->content[0] == '\0') ? 0 : 1;
		ft_strdel(&(r->content));
	}
	return (r);
}

int				sh_gnl(t_shell *sh, int const fd, char **line)
{
	size_t			reading_ok;

	if (!line || fd < 0 || !(sh->gnl = fd_already_stored(fd, sh->gnl))
	|| !(sh->gnl->buff = ft_strnew(sizeof(char) * BUFF_SIZE)))
		return (-1);
	reading_ok = 1;
	while (reading_ok)
	{
		if ((sh->gnl->rr = read(sh->gnl->fd, sh->gnl->buff, BUFF_SIZE)) == -1)
			return (-1);
		sh->gnl->buff[sh->gnl->rr] = '\0';
		sh->gnl->content = ft_strjoinf(sh->gnl->content, sh->gnl->buff, 1);
		if (ft_strchrs(sh->gnl->content, '\n')
		|| (sh->gnl->rr >= 0 && sh->gnl->rr < BUFF_SIZE))
		{
			sh->gnl = manipulate_data(sh->gnl, line);
			reading_ok = 0;
		}
		ft_strclr(sh->gnl->buff);
	}
	ft_strdel(&(sh->gnl->buff));
	return (handle_r(&sh->gnl));
}
