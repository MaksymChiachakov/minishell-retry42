/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:29:09 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/05 20:15:46 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_command *cmd)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("minishell: pwd"), 1);
	write(cmd->outfd, cwd, ft_strlen(cwd));
	write(cmd->outfd, "\n", 1);
	return (0);
}
