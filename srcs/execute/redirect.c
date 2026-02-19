/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:45:04 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/19 13:55:07 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	is_eof(char *line, t_token eof)
{
	char	*delimiter;
	int		result;

	delimiter = ft_substr(eof.str, 0, eof.len);
	result = ft_strcmp(line, delimiter);
	free(delimiter);
	return (result == 0);
}

int	syntax_error(t_env *e, t_token t)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	write(2, t.str, t.len);
	ft_putstr_fd("'\n", 2);
	e->should_exit = true;
	e->code_exit = 2;
	return (-1);
}

int	system_error(t_env *e, char *name)
{
	(void)e;
	ft_putstr_fd("minishell: ", 2);
	perror(name);
	return (-1);
}

void handle_sigint_heredoc(int sig)
{
    (void)sig;

    g_signal = SIGINT;
    write(1, "\n", 1);
    rl_done = 1;
}

void setup_signals_heredoc(struct sigaction *old)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old);
}



int	heredoc(t_env *e, t_command *cmd)
{
	char	*line;
	t_token	eof;
	int		fds[2];
	struct sigaction	sa_old;
	
	if (pipe(fds) == -1)
		return (system_error(e, "minishell: pipe: "));
	eof = get_next_token(e);
	if (eof.kind != TOKEN_WORD)
		return (syntax_error(e, eof));
	setup_signals_heredoc(&sa_old);
	g_signal = 0;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (g_signal == SIGINT)
		{
			free(line);
			close(fds[0]);
			close(fds[1]);
			cmd->infd = -1;
			e->code_exit = 130;
			g_signal = 0;
			write(1, "\n", 1);
			sigaction(SIGINT, &sa_old, NULL);
			setup_signals();
			return (-1);
		}
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_eof(line, eof))
		{
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	write(1, "\n", 1);
	sigaction(SIGINT, &sa_old, NULL);
	setup_signals();
	return (heredoc_supp(cmd, fds));
}

int	open_file(t_env *e, t_command *cmd, int flag)
{
	t_token	t;
	char	*filename;
	int		fd;

	t = get_next_token(e);
	if (t.kind != TOKEN_WORD)
		return (syntax_error(e, t));
	if (cmd->infd == -1 || cmd->outfd == -1)
		return (-1);
	if (t.len == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
			token 'newline'\n", 2);
		e->code_exit = 2;
		cmd->infd = -1;
		return (-1);
	}
	filename = expand(e, t);
	if (!filename)
		return (-1);
	fd = open(filename, flag, 0644);
	if (fd == -1)
		system_error(e, filename);
	free(filename);
	return (fd);
}
