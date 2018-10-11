/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/11 02:56:42 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static char			*move_past_leading_spaces(char *content)
{
	while (content && *content == ' ')
		content++;
	return (content);
}

static bool			contains_printable_characters(char *str)
{
	while (str && *str)
	{
		if (ft_isprint(*str))
			return (true);
		str++;
	}
	return (false);
}

static char			*get_auto_mode(t_shell *sh, char *content)
{
	char			*str;
	char			*slash;

	if (!(str = ft_strrchr(move_past_leading_spaces(content), ' ')))
	{
		str = content;
		sh->ac->auto_mode = (*str != '.') ? AUTO_BIN : AUTO_REG;
		if (*str == '$')
		{
			sh->ac->auto_mode = AUTO_ENV;
			str++;
		}
		sh->ac->pre_file_name = ft_strnew(0);
	}
	else
	{
		str++;
		if (*str == '$')
		{
			sh->ac->auto_mode = AUTO_ENV;
			str++;
		}
		else
			sh->ac->auto_mode = AUTO_REG;
		if ((slash = ft_strrchr(str, '/')))
			sh->ac->pre_file_name = ft_strndup(content, (slash - content) + 1);
		else
			sh->ac->pre_file_name = ft_strndup(content, (str - content));
	}
	if (!contains_printable_characters(content) || !sh->ac->pre_file_name
			|| sh->ac->auto_mode == AUTO_NON)
		return (NULL);
	return (str);
}

static bool			create_ac(t_shell *sh, char *str)
{
	if (!(sh->ac->argv = (char **)malloc(sizeof(char *) * 3)))
		return (false);
	sh->ac->argv[0] = str;
	sh->ac->argv[1] = str;
	sh->ac->argv[2] = NULL;
	return (true);
}

static char			*get_env_var(t_shell *sh, char *ptr_to_dollar, int len)
{
	char			**environment;
	char			*env;
	int				total;

	total = 0;
	env = NULL;
	environment = sh->env->environment;
	while (*environment)
	{
		if (!ft_strncmp(*environment, ptr_to_dollar + 1, len - 1))
		{
			env = *environment;
			if (++total > 1)
				return (NULL);
		}
		environment++;
	}
	return (env);
}

static bool				auto_env(t_shell *sh)
{
	int				len;
	char			*env;
	char			*track;
	char			*ptr_to_dollar;

	if ((ptr_to_dollar = ft_strrchr(sh->buffer.content, ' ')))
		ptr_to_dollar++;
	else
		ptr_to_dollar = sh->buffer.content;
	if (*ptr_to_dollar != '$')
		return (false);

	len = ft_strlen(ptr_to_dollar + 1) + 1;
	if(!(env = get_env_var(sh, ptr_to_dollar, len)))
		return (false);
	if (!env
			|| !ft_strchr(env, '=')
			|| ft_strncmp(env, ptr_to_dollar + 1, ft_strchr(env, '=') - env)
			|| !(env = ft_strchr(env, '=') + 1))
		return (false);
	track = sh->buffer.content;
	sh_move_home(sh);
	while (track++ != ptr_to_dollar)
		sh_move_right(sh);
	while (len--)
		sh_delete_current_char(sh);
	sh_print_str(sh, env);
	sh_move_end(sh);
	return (true);
}

bool				auto_completion(t_shell *sh)
{
	bool			performed_completion;
	char			*parsed_buffer;

	performed_completion = false;
	sh->modes.auto_completion = 1;
	if (auto_history(sh) || auto_env(sh))
		performed_completion = true;
	else if (!ft_strcmps(sh->read->line, K_TAB))
	{
		sh_move_end(sh);
		if (!(sh->ac = (t_ac *)malloc(sizeof(t_ac))))
			return (false);
		ft_bzero(sh->ac, sizeof(t_ac));
		if (!(parsed_buffer = get_auto_mode(sh, sh->buffer.content)))
			return (false);
		if (create_ac(sh, parsed_buffer)
				&& auto_get_obj(sh))
			auto_issuance(sh);
		auto_free_ac(sh);
		performed_completion = true;
	}
	sh->modes.auto_completion = 0;
	return (performed_completion);
}
