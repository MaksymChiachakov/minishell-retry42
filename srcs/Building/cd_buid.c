/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_buid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:13:02 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/13 10:09:31 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_env(t_env *env)
{
	char	cwd[1024];
	char	*oldpwd;
	char	*cwd_copy;

	if (getcwd(cwd, sizeof(cwd)))
	{
		oldpwd = get_env_value("PWD", env);
		if (oldpwd)
		{
			set_env_value("OLDPWD", oldpwd, env);
			free(oldpwd);
		}
		cwd_copy = ft_strdup(cwd);
		if (!cwd_copy)
			return ;
		set_env_value("PWD", cwd_copy, env);
		free(cwd_copy);
	}
}

int	ft_cd(t_command *cmd, t_env *env)
{
	char	*p;

	if (!cmd->args[1])
		p = get_env_value("HOME", env);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		p = get_env_value("OLDPWD", env);
		if (!p)
			return (print_error("cd", NULL, "OLDPWD not set"), 1);
		write(cmd->outfd, p, ft_strlen(p));
		write(cmd->outfd, "\n", 1);
	}
	else if (cmd->args[2])
		return (print_error("cd", NULL, "too many arguments"), 1);
	else
		p = ft_strdup(cmd->args[1]);
	if (!p)
		return (print_error("cd", NULL, "HOME not set"), 1);
	if (chdir(p) == -1)
		return (free(p), print_error("cd", cmd->args[1], strerror(errno)), 1);
	return (update_pwd_env(env), free(p), 0);
}
