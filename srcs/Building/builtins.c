/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:12:54 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/17 12:39:25 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return ((!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
				"echo") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")));
}

int	exec_builtin(t_command *cmd, t_env *env)
{
	int	result;

	result = env->code_exit;
	if (!ft_strcmp(cmd->args[0], "pwd"))
		result = builtin_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		result = echo_build(cmd, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		result = ft_cd(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		result = ft_exit(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		result = ft_unset(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "export"))
		result = ft_export(cmd, env);
	else if (!ft_strcmp(cmd->args[0], "env"))
		result = ft_env(cmd, env);
	if (cmd->infd != STDIN_FILENO)
		close(cmd->infd);
	if (cmd->outfd != STDOUT_FILENO)
		close(cmd->outfd);
	return (result);
}
