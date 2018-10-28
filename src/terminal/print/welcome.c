/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:38:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 17:06:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_welcome_move(void)
{
	ft_putendl("\nMove");
	ft_putendl("  ← .............. move one char to left");
	ft_putendl("  → .............. move one char to right");
	ft_putendl("  ↖ .............. move to begining of line");
	ft_putendl("  ↘ .............. move to end of line");
	ft_putendl("  ⌥ + ← .......... move one word to left");
	ft_putendl("  ⌥ + → .......... move one word to right");
	ft_putendl("  ⌥ + ↑ .......... move one row up");
	ft_putendl("  ⌥ + ↓ .......... move one row down");
}

static void	sh_welcome_select(void)
{
	ft_putendl("\nSelect");
	ft_putendl("  ⇧ + ← .......... select left char");
	ft_putendl("  ⇧ + → .......... select right char");
	ft_putendl("  ⇧ + ↖ .......... select chars to begining of line");
	ft_putendl("  ⇧ + ↘ .......... select chars to end of line");
	ft_putendl("  ⇧ + ⌥ + ← ...... select left word");
	ft_putendl("  ⇧ + ⌥ + → ...... select right word");
	ft_putendl("  ⇧ + ⌥ + ↑ ...... select row above");
	ft_putendl("  ⇧ + ⌥ + ↓ ...... select row below");
	ft_putendl("  Ctrl + K ....... copy");
	ft_putendl("  Ctrl + X ....... cut");
	ft_putendl("  Ctrl + P ....... paste");
}

static void	sh_welcome_delete(void)
{
	ft_putendl("\nDelete");
	ft_putendl("  del ............ delete previous char");
	ft_putendl("  fn + del ....... delete current char");
	ft_putendl("  Ctrl + A ....... delete all");
	ft_putendl("  Ctrl + E ....... delete to end of line");
	ft_putendl("  Ctrl + H ....... delete to begining of line");
	ft_putendl("  Ctrl + B ....... delete previous word");
	ft_putendl("  Ctrl + F ....... delete next word");
}

static void	sh_welcome_history(void)
{
	ft_putendl("\nHistory");
	ft_putendl("  ↑ .............. previous command");
	ft_putendl("  ↓ .............. next command");
	ft_putendl("  Ctrl + R ....... search command");
	ft_putendl("  !! ............. gets last command");
	ft_putendl("  !27 ............ gets command with id 27");
	ft_putendl("  !-42 ........... gets 42nd most recent command");
	ft_putendl("  !foo ........... gets command by strncmp(cmd, \"foo\", 3)");
	ft_putendl("  !?foo .......... gets command by strstr(cmd, \"foo)\")");
	ft_putendl("  bar!?foo?bar ... gets command by strstr(cmd, \"foo)\")");
	ft_putendl("  ^foo^bar^ ...... gets last command but applies s/foo/bar");
}

void		sh_welcome(void)
{
	ft_putendl("Welcome");
	sh_welcome_move();
	sh_welcome_select();
	sh_welcome_delete();
	sh_welcome_history();
}
