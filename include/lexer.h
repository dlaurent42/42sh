/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:03:40 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 14:34:26 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

typedef enum    e_token_type
{
    TOKEN_NULL = 0,
    TOKEN_ANDIF = 1,
    TOKEN_ORIF = 2,
    TOKEN_REDIR = 3,
    TOKEN_SEMICOLON = 4,
    TOKEN_PIPE = 5,
    TOKEN_BLANK = 6,
    TOKEN_SINGLEQUOTE = 7,
    TOKEN_DOUBLEQUOTE = 8,
    TOKEN_BACKQUOTE = 9,
    TOKEN_AGGREG = 10,
    TOKEN_MERGE = 11,
    TOKEN_WORD = 12
}               t_token_type;

typedef struct      s_token
{
    char            *id;
    int             size;
    t_token_type    type;
}                   t_token;

typedef struct  s_lexer
{
    t_token     *tokens;
    size_t      capacity;
    size_t      size;
    char        *cmd;

}               t_lexer;

void            lexer_entry(char *cmd);
void            lexer_fill(t_lexer *lexer, const char *cmd);
t_token         *lexer_token_search(const char *cmd);
const t_token   *lexer_lexic_singletone(void);
void            lexer_token_add(t_lexer *lexer, const char *src, size_t size, t_token_type type);
void            lexer_delete(t_lexer *lexer);
void            lexer_token_singlequote(t_lexer *lexer, const char **cmd);
void            lexer_token_doublequote(t_lexer *lexer, const char **cmd);
void            lexer_token_backquote(t_lexer *lexer, const char **cmd);

#endif