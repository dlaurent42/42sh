/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 02:53:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 02:59:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		term_delete(t_shell *shell)
{
	if (!shell || !shell->term)
		return ;
	if (tcgetattr(0, &(shell->term)) == -1)
		return ;
	shell->term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &(shell->term)) == -1)
		return ;
}
