/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:45:56 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/19 14:22:47 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

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

int	heredoc_supp_finish(t_command *cmd, int fds[2], struct sigaction *sa_old)
{
	write(1, "\n", 1);
	sigaction(SIGINT, sa_old, NULL);
	setup_signals();
	close(fds[1]);
	if (cmd->infd == -1 || cmd->outfd == -1)
		return (close(fds[0]), -1);
	return (fds[0]);
}
