/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:45:56 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/09 20:14:34 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_supp(t_command *cmd, int fds[2])
{
	close(fds[1]);
	if (cmd->infd == -1 || cmd->outfd == -1)
		return (close(fds[0]), -1);
	return (fds[0]);
}
