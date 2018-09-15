/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 20:21:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 22:25:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_set_prompt_properties(t_term *term, unsigned char has_git)
{
	unsigned char	i;

	i = 0;
	term->prompt.display_length = 0;
	while (term->prompt.content[i])
	{
		if (term->prompt.content[i] >= 0b11000000
		|| term->prompt.content[i] < 0b10000000)
			term->prompt.display_length++;
		i++;
	}
	term->prompt.display_length -= (has_git) ? 54 : 24;
	term->prompt.display_length_mod = term->prompt.display_length % term->window.width;
}

static char	*term_get_folder_name(t_env *env, char *location, size_t length)
{
	if (ft_strcmps((char *)location, env_search(env, "HOME")) == 0)
		return (ft_strdup("~"));
	if (length == 1 && location[0] == '/')
		return (ft_strdup("/"));
	(location[length - 1] == '/') ? location[length--] = '\0' : 0;
	if ((location[0] == '/' && ft_strcountif((char *)location, '/') == 1))
		return (ft_strdup(location));
	length--;
	while (location[length] && location[length] != '/')
		length--;
	return (ft_strdups(location + length + 1));
}

static char	*parse_git_branch(char *str)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	j = i;
	while (str[j] && str[j] != '\n')
		j++;
	if (i + 2 >= j && j - i - 1 > 0)
		return (NULL);
	output = ft_strsub(str, i + 2, j - i - 2);
	ft_strdel(&str); 
	output = ft_strjoinf(" \e[1;34;40mgit:[\e[1;31;40m", output, 2);
	output = ft_strjoinf(output, "\e[1;34;40m]", 1);
	return (output);
}

static char	*term_get_git_branch(t_shell *shell)
{
	char			*args[3];
	char			*output;
	t_bin_obj		*obj;

	args[0] = "git";
	args[1] = "branch"; 
	args[2] = NULL;
	if (!(obj = bin_search(shell->bin, "git")))
		return (NULL);
	if (!(output = bin_execute_fetch(shell, obj->path, args)))
		return (NULL);
	return (parse_git_branch(output));
}

void		term_set_prompt(t_shell *shell, t_term *term, char *location)
{
	char	*git;
	size_t	length;

	git = NULL;
	(term->prompt.content) ? ft_strdel((char **)&term->prompt.content) : 0;
	(term->prompt.location) ? ft_strdel((char **)&term->prompt.location) : 0;
	term->prompt.location = (unsigned char *)ft_strdups(location);
	if ((length = ft_strlens((char *)location)) == 0)
		return ;
	term->prompt.content = (unsigned char *)ft_strjoinf("\e[1;32;40m", term_get_folder_name(shell->env, location, length), 2);
	if ((git = term_get_git_branch(shell)))
		term->prompt.content = (unsigned char *)ft_strjoinf((char *)term->prompt.content, git, 3);
	term->prompt.content = (unsigned char *)ft_strjoinf((char *)term->prompt.content, " \e[1;32;40m▸\033[0m ", 1);
	(git)
		? sh_set_prompt_properties(term, 1)
		: sh_set_prompt_properties(term, 0);
}
