/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:44:47 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/14 14:02:53 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->infd = 0;
	cmd->outfd = 0;
	cmd->args = ft_calloc(1, sizeof(char *));
	if (cmd->args == NULL)
		return (free(cmd), NULL);
	return (cmd);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	free_command(cmd->next);
	if (cmd->infd > 2)
		close(cmd->infd);
	if (cmd->outfd > 2)
		close(cmd->outfd);
	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	free(cmd);
}
