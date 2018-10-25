/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:44:04 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/25 12:04:20 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** TODO: check if you really need to close fd
 */
static char	single_left_cursor(t_shell *sh, t_token_tree *tree, int fd)
{
	int		stdin;
	char	ret;

	stdin = dup(0);
	dup2(fd, 0);
	ret = execute_tree(sh, tree->left);
	dup2(stdin, 0);
	close(stdin);
	return (ret);
}

char		execute_left_redirection(t_shell *sh, t_token_tree *tree)
{
	int					fd;
	int					type;
	char				*file;
	t_token_tree		*last;

	last = tree->right;
	type = (!ft_strcmp(tree->tokens[0], "<<") ? 2 : 1);
	while (last)
	{
		file = (last->left) ? last->left->tokens[0] : last->tokens[0];
		if (type == 1 && ((fd = open(file, O_RDONLY)) == -1)) // TODO: need to check file permission!!!!
			return (error_execution_file(file));
		if (type == 1)
			single_left_cursor(sh, tree, fd);
		// (last->left && last->right) ? close(fd) : 0;
		if (last->right)
			type = (!ft_strcmp(tree->tokens[0], "<<") ? 2 : 1);
		last = last->right;
	}
	// if (type == 1)
	// 	single_left_cursor(sh, tree, fd);
	/*
	else if (!left_cursor_heredoc(tree))
		return (-1);*/
	return (0);
}
