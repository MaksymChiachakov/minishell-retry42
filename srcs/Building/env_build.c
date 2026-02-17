/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:13:17 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/05 20:18:24 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_command *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strchr(env->envp[i], '='))
		{
			write(cmd->outfd, env->envp[i], ft_strlen(env->envp[i]));
			write(cmd->outfd, "\n", 1);
		}
		i++;
	}
	return (0);
}
