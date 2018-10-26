/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 23:43:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/26 02:19:56 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			parse_obj(t_shell *sh, char *initial_file_name)
{
	char			*path;
	char			*ptr_to_last_word;
	t_obj			*obj;

	if (!(obj = auto_create_obj()))
		return (false);
	ptr_to_last_word = ft_strrchr(sh->buffer.content + sh->buffer.ushift, ' ');
	if (ptr_to_last_word && *(ptr_to_last_word + 1) == '/')
		path = ft_strdups("/");
	else if (ptr_to_last_word && *(ptr_to_last_word + 1) == '~')
	{
		path = ft_strdups(env_search(sh->env, "HOME"));
		initial_file_name++;
	}
	else
		path = ft_strdups(".");
	if (!path || !(auto_path(obj, path, initial_file_name)))
	{
		free(obj);
		return (false);
	}
	free(path);
	sh->ac->obj = obj;
	return (true);
}

static bool			get_binaries(t_shell *sh)
{
	t_obj			*obj;
	t_obj			*last_obj;
	t_bin_auto		*bin_auto;

	last_obj = NULL;
	bin_auto = sh->bin->bin_auto;
	while (bin_auto)
	{
		if (!(obj = auto_create_obj()))
			return (false);
		obj->data.bin = 1;
		if (!(obj->data.str = ft_strdups(bin_auto->name)))
		{
			free(obj);
			return (false);
		}
		if (!sh->ac->bin)
			sh->ac->bin = obj;
		else if (last_obj)
			last_obj->next = obj;
		last_obj = obj;
		bin_auto = bin_auto->next;
	}
	return (true);
}

static bool			get_env(t_shell *sh, char **env)
{
	t_obj			*obj;
	t_obj			*last_obj;
	char			*equals;

	last_obj = NULL;
	while (*env)
	{
		if (!(equals = ft_strchr(*env, '=')))
			break ;
		if (!(obj = auto_create_obj()))
			return (false);
		obj->data.env = 1;
		if (!(obj->data.str = ft_strndup(*env, equals - *env)))
		{
			free(obj);
			return (false);
		}
		if (!sh->ac->env)
			sh->ac->env = obj;
		else if (last_obj)
			last_obj->next = obj;
		last_obj = obj;
		env++;
	}
	return (true);
}

bool				auto_get_obj(t_shell *sh)
{
	if (sh->ac->auto_mode != AUTO_NON)
	{
		if (!(parse_obj(sh, sh->ac->initial_file_name)))
			return (false);
	}
	if (sh->ac->auto_mode == AUTO_BIN)
	{
		if (!(get_binaries(sh)))
			return (false);
	}
	if (sh->ac->auto_mode == AUTO_BIN || sh->ac->auto_mode == AUTO_ENV)
	{
		if (!(get_env(sh, sh->env->environment)))
			return (false);
	}
	return (true);
}
