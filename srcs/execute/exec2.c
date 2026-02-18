/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:52:13 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/18 13:03:53 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

char	*get_bin(t_env *e, char *name)
{
	char	**paths;
	char	*bin;
	int		i;

	if (name[0] == '/' || name[0] == '.')
		return (ft_strdup(name));
	i = -1;
	paths = NULL;
	while (e->envp[++i])
		if (ft_strncmp(e->envp[i], "PATH=", 5) == 0)
			paths = ft_split(e->envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		bin = join_path(paths[i], name);
		if (!bin)
			return (free_split(paths), NULL);
		if (access(bin, X_OK) == 0)
			break ;
		bin = (free(bin), NULL);
	}
	free_split(paths);
	return (bin);
}

void	execute_commands_supp(t_env *e, t_command *cmd)
{
	char	*bin;

	bin = get_bin(e, cmd->args[0]);
	if (bin == NULL)
		(print_error(cmd->args[0], NULL, "command not found"), fexit(e, 127));
	if (bin[0] == '.' || bin[0] == '/')
		check_execuable_error(e, bin);
	if (cmd->infd != STDIN_FILENO)
		(dup2(cmd->infd, STDIN_FILENO), close(cmd->infd));
	if (cmd->outfd != STDOUT_FILENO)
		(dup2(cmd->outfd, STDOUT_FILENO), close(cmd->outfd));
	if (cmd->next)
		close(cmd->next->infd);
	execve(bin, cmd->args, e->envp);
	(ft_putstr_fd("minishell: ", 2), perror(bin), free(bin), fexit(e, 127));
}

void	handle_exec_end(t_env *e, int pid, int status)
{
	if (pid != -1)
		waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (pid != -1)
		handle_parent_signals(e, status);
	else
		e->code_exit = 1;
		
	clear_command(e);

}

void	process_command_pipeline(t_env *e)
{
	t_command	*cmd;
	int			pid;
	int			status;

	cmd = e->cmd;
	pid = 0;
	status = 0;
	ignore_signals();
	while (cmd)
	{
		if (!pipe_command(cmd))
			pid = execute_command(e, cmd);
		else
			pid = -1;
		cmd = cmd->next;
	}
	handle_exec_end(e, pid, status);
}
