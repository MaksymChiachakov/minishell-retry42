/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:33:34 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/13 09:33:20 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	eat_op(char *s)
{
	t_token	token;

	token.kind = TOKEN_OP;
	token.str = s;
	if (s[0] == '|')
		token.len = 1;
	else if (s[0] == '>' && s[1] == '>')
		token.len = 2;
	else if (s[0] == '<' && s[1] == '<')
		token.len = 2;
	else if (s[0] == '>')
		token.len = 1;
	else if (s[0] == '<')
		token.len = 1;
	return (token);
}

int	eat_quote(char s[0], char quote, t_env *e)
{
	int	len;

	len = 1;
	while (s[len] && s[len] != quote)
		len++;
	if (s[len] != quote)
	{
		ft_putstr_fd("minishell: missing closing quote\n", 2);
		e->should_exit = true;
		e->code_exit = 1;
		return (INT_MIN);
	}
	len++;
	return (len);
}

t_token	eat_word(char *s, t_env *e)
{
	t_token	token;

	if (s[0] == '|' || s[0] == '>' || s[0] == '<')
		return (eat_op(s));
	token.len = 0;
	token.str = s;
	token.kind = TOKEN_WORD;
	while (s[token.len])
	{
		if (is_whitespace(s[token.len]) || is_shell_operator(s[token.len]))
			break ;
		if (s[token.len] == '\'' || s[token.len] == '"')
			token.len += eat_quote(s + token.len, s[token.len], e);
		else
			token.len++;
		if (token.len < 0)
			return (token);
	}
	return (token);
}

t_token	get_next_token(t_env *e)
{
	t_token	token;

	token = peek_next_token(e);
	if (token.kind != ERROR)
		e->index += token.len;
	return (token);
}

t_token	peek_next_token(t_env *e)
{
	t_token	token;

	while (is_whitespace(e->command[e->index]))
		e->index++;
	if (e->command[e->index] == '\0')
	{
		token.len = 0;
		token.kind = TOKEN_EOF;
		return (token);
	}
	token = eat_word(e->command + e->index, e);
	if (token.len <= 0)
		token.kind = ERROR;
	return (token);
}
