/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 00:19:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 21:16:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Command Line history
**
** -----------------------------------------------------------------------------
**
** Syntax
** 	     history
** 	     history [n]
** 	     history -c
** 	     history -d offset
** 	     history [-anrw] [filename]
** 	     history -ps arg
**
** Options
**    -c   Clear the history list. This can be combined with the other
**         options to replace the history list completely.
**
**    -d offset
**         Delete the history entry at position offset.
**         offset should be specified as it appears when the history is
**         displayed.
**
**    -a   Append the new history lines (history lines entered since
**         the beginning of the current Bash session) to the history file.
**
**    -n   Append the history lines not already read from the history file
**         to the current history list. These are lines appended to the
**         history file since the beginning of the current Bash session.
**
**    -r   Read the current history file and append its contents to the history
**         list.
**
**    -w   Write out the current history to the history file.
**
**    -p   Perform history substitution on the args and display the result
**         on the standard output, without storing the results in the history
**         list.
**
**    -s   The args are added to the end of the history list as a single entry.
**
** With no options, display the history list with line numbers. Lines prefixed
** with a `*' have been modified. An argument of n lists only the last n lines.
**
** When any of the `-w', `-r', `-a', or `-n' options are used, if filename
** is given, then it is used as the history file. If not, then the value of
** the HISTFILE variable is used.
**
** -----------------------------------------------------------------------------
**
** Event Designators
**
** An event designator is a reference to a command line entry in the history
** list.
** !             Start a history substitution, except when followed by a space,
**               tab, the end of the line, `=' or `('.
**
** !n            Refer to command line n.
**
** !-n           Refer to the command n lines back.
**
** !!            Refer to the previous command. This is a synonym for `!-1'.
**
** !string       Refer to the most recent command starting with string.
**
** !?string[?]   Refer to the most recent command containing string.
**               The trailing `?' can be omitted if the string is followed
**               immediately by a newline.
**
** ^string1^string2^   Quick Substitution. Repeat the last command, replacing
**				 string1 with string2. Equivalent to !!:s/string1/string2/.
**
** !#            The entire command line typed so far.
**
** -----------------------------------------------------------------------------
**
** Word Designators
**
** Word designators are used to select desired words from the event.
** A `:' separates the event specification from the word designator.
** It can be omitted if the word designator begins with a `^', `$', `*', `-',
** or `%'. Words are numbered from the beginning of the line, with the first
** word being denoted by 0 (zero). Words are inserted into the current line
** separated by single spaces.
**
** For example,
**
** !!      designates the preceding command. When you type this, the
**         preceding command is repeated in toto.
**
** !!:$    designates the last argument of the preceding command.
**         This can be shortened to !$.
**
** !fi:2   designates the second argument of the most recent command
**         starting with the letters fi.
**
** Here are the word designators:
**
** 0 (zero) The 0th word. For many applications, this is the command word.
**
** n        The nth word.
**
** ^        The first argument; that is, word 1.
**
** $        The last argument.
**
** %        The word matched by the most recent `?string?' search.
**
** x-y      A range of words; `-y' abbreviates `0-y'.
**
** *        All of the words, except the 0th. This is a synonym for `1-$'.
**          It is not an error to use `*' if there is just one word in the
** 			event; the empty string is returned in that case.
**
** x*       Abbreviates `x-$'
**
** x-       Abbreviates `x-$' like `x*', but omits the last word.
**
** If a word designator is supplied without an event specification,
** the previous command is used as the event.
**
** -----------------------------------------------------------------------------
**
** Modifiers
**
** After the optional word designator, you can add a sequence of one or more
** of the following modifiers, each preceded by a `:'.
**
** h   Remove a trailing pathname component, leaving only the head.
**
** t   Remove all leading pathname components, leaving the tail.
**
** r   Remove a trailing suffix of the form `.suffix', leaving the basename.
**
** e   Remove all but the trailing suffix.
**
** p   Print the new command but do not execute it.
**
** q   Quote the substituted words, escaping further substitutions.
**
** x   Quote the substituted words as with `q', but break into words at
**     spaces, tabs, and newlines.
**
** s/old/new/
**     Substitute new for the first occurrence of old in the event line.
**     Any delimiter can be used in place of `/'. The delimiter can be
**     quoted in old and new with a single backslash.
**     If `&' appears in new, it is replaced by old.
**     A single backslash will quote the `&'.
**     The final delimiter is optional if it is the last character on the
**     input line.
**
** &   Repeat the previous substitution.
**
** g   Cause changes to be applied over the entire event line.
**     Used in conjunction with `s', as in gs/old/new/, or with `&'.
** History Configuration
** export HISTCONTROL=erasedups
** export HISTSIZE=10000
** shopt -s histappend
**
** # Remove duplicates from history (when a new item is added).
** # Increase the history size.
** # Append history to ~/.bash_history. when you exit a shell
** From Allan Odgaard’s excellent Working With History in Bash
**
** set show-all-if-ambiguous on - Alters the default behavior of the completion
** functions. If set to ‘on’, words which have more than one possible completion
** cause the matches to be listed immediately instead of ringing the bell.
** set completion-ignore-case on - Case insensitive matching (Readline).
*/

char	sh_history(t_shell *sh, t_env *env, char **argv)
{
	int		i;

	i = 0;
	if (!argv || !argv[0])
		return (sh_history_print(sh));
	if (argv[0] && !sh_is_option_string(argv[0], "cdspwarn"))
	{
		i += (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
			? 1 : 0;
		if (!argv[i])
			return (sh_history_print(sh));
		if (argv[i + 1])
			return (sh_history_error(2));
		if (!ft_isint(argv[i]) || (i = ft_atoi(argv[i])) == INT32_MIN)
			return (sh_history_error(1));
		if (i < 0)
			i *= (-1);
		return (sh_history_print_shift(sh, i));
	}
	return (sh_history_options(sh, env, argv));
}
