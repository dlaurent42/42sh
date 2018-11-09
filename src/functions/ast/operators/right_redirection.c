/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:46:49 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 17:22:22 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** stdout - 0
** stderr - 1
*/

static char	execute_on_right(t_shell *sh, t_token_tree *tree, int fd)
{
	char		ret;
	char		*descriptor;
	int			std[2];
	int			both;
	size_t		len;

	len = 0;
	while (tree->tokens[0][len] && tree->tokens[0][len] != '>')
		len++;
	descriptor = (len == 0 ? NULL : ft_strndup(tree->tokens[0], len));
	both = (descriptor && *descriptor == '&') ? 1 : 0;
	std[0] = dup(descriptor && !both ? ft_atoi(descriptor) : 1);
	(both) ? std[1] = dup(2) : (0);
	dup2(fd, descriptor && !both ? ft_atoi(descriptor) : 1);
	(both) ? dup2(fd, 2) : (0);
	ret = execute_tree(sh, tree->left);
	dup2(std[0], descriptor && !both ? ft_atoi(descriptor) : 1);
	(both) ? dup2(std[1], 2) : (0);
	close(std[0]);
	(both) ? close(std[1]) : (0);
	ft_strdel(&descriptor);
	return (ret);
}

char		execute_right_redirection(t_shell *sh, t_token_tree *tree)
{
	int				fd;
	int				ops;
	char			*file;
	t_token_tree	*last;

	last = tree->right;
	ops = O_WRONLY | O_CREAT;
	ops |= ((!ft_strcmp(tree->tokens[0], ">>")) ? O_APPEND : O_TRUNC);
	while (last)
	{
		if (last->type == 1)
		{
			ops = O_WRONLY | O_CREAT;
			ops |= ((!ft_strcmp(tree->tokens[0], ">>")) ? O_APPEND : O_TRUNC);
		}
		file = (last->left ? last->left->tokens[0] : last->tokens[0]);
		if ((fd = open(file, ops, 0644)) == -1)
			return (error_file_permissions(sh, file));
		(last->left && last->right ? close(fd) : 0);
		last = last->right;
	}
	return (execute_on_right(sh, tree, fd));
}
