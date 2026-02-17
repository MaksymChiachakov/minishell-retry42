/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:24:27 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/17 12:50:13 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_env *e, t_command *cmd)
{
	int	pid;

	if (cmd->args[0] == NULL)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		handle_child_signals();
		if (is_builtin(cmd->args[0]))
			exit(exec_builtin(cmd, e));
		execute_commands_supp(e, cmd);
	}
	if (cmd->infd != STDIN_FILENO)
		close(cmd->infd);
	if (cmd->outfd != STDOUT_FILENO)
		close(cmd->outfd);
	return (pid);
}

int	pipe_command(t_command *cmd)
{
	int	pipefds[2];
	int	error;

	error = ((cmd->infd == -1) || (cmd->outfd == -1));
	if (!cmd->next)
	{
		if (cmd->outfd == 0)
			cmd->outfd = STDOUT_FILENO;
		return (error);
	}
	pipe(pipefds);
	if (cmd->outfd == 0 && !error)
		cmd->outfd = pipefds[1];
	else
		close(pipefds[1]);
	if (cmd->next->infd == 0 && !error)
		cmd->next->infd = pipefds[0];
	else
		close(pipefds[0]);
	return (error);
}

void	handle_parent_signals(t_env *e, int status)
{
	int	sig;

	if (WIFEXITED(status))
		e->code_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		e->code_exit = 128 + sig;
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
}

void	execute_commands(t_env *e)
{
	t_command	*first_cmd;
	t_command	*cmd;

	first_cmd = parse(e);
	cmd = first_cmd;
	if (cmd == NULL)
		return ;
	if (cmd->args[0] == NULL && cmd->infd <= 0 && cmd->outfd <= 0 && !cmd->next)
	{
		e->code_exit = ((cmd->infd == -1) || (cmd->outfd == -1));
		free_command(cmd);
		return ;
	}
	if (!cmd->next && is_builtin(cmd->args[0]))
	{
		if (!pipe_command(cmd))
			e->code_exit = exec_builtin(cmd, e);
		else
			e->code_exit = 1;
		free_command(cmd);
		return ;
	}
	process_command_pipeline(e, first_cmd);
}
