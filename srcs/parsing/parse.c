/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:29:06 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/13 17:29:00 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(t_token t, char *op)
{
	return (t.kind == TOKEN_OP && ft_strncmp(t.str, op, t.len) == 0);
}

char	*take_next_word(t_env *e)
{
	t_token	t;

	t = get_next_token(e);
	if (t.kind != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(t.str, 2);
		ft_putstr_fd("'\n", 2);
		e->should_exit = true;
		e->code_exit = 1;
		return (NULL);
	}
	return (expand(e, t));
}

int	parse_arg(t_env *e, t_command *cmd, t_token t)
{
	if (t.kind == TOKEN_WORD)
		ft_append(&cmd->args, expand(e, t));
	else if (is_op(t, "<"))
		cmd->infd = open_file(e, cmd, O_RDONLY);
	else if (is_op(t, ">"))
		cmd->outfd = open_file(e, cmd, O_WRONLY | O_CREAT | O_TRUNC);
	else if (is_op(t, "<<"))
		cmd->infd = heredoc(e, cmd);
	else if (is_op(t, ">>"))
		cmd->outfd = open_file(e, cmd, O_WRONLY | O_CREAT | O_APPEND);
	else
		return (true);
	return (false);
}

t_command	*parse_next(t_env *e)
{
	t_token		t;
	t_command	*cmd;

	cmd = create_command();
	if (cmd == NULL)
		return (NULL);
	if (is_op(peek_next_token(e), "|"))
		return (flag_error(e, "parse", "|", "unexpected token"),
			free_command(cmd), NULL);
	while (e->should_exit == false)
	{
		t = get_next_token(e);
		if (parse_arg(e, cmd, t) == true)
			break ;
	}
	if (e->should_exit)
		return (free_command(cmd), NULL);
	if (is_op(t, "|"))
		cmd->next = parse_next(e);
	else if (t.kind != TOKEN_EOF)
		return (flag_error(e, "parse", t.str, "unexpected token"), NULL);
	return (cmd);
}

t_command	*parse(t_env *e)
{
	t_command	*cmd;

	e->index = 0;
	cmd = parse_next(e);
	if (e->should_exit)
	{
		e->should_exit = false;
		return (free_command(cmd), NULL);
	}
	return (cmd);
}
