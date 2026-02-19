/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:45:56 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/19 15:08:05 by mchiacha         ###   ########.fr       */
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

/* heredoc support finish */
int	hsf(t_command *c, int f[2], struct sigaction *s)
{
	write(1, "\n", 1);
	sigaction(SIGINT, s, NULL);
	setup_signals();
	close(f[1]);
	if (c->infd == -1 || c->outfd == -1)
		return (close(f[0]), -1);
	return (f[0]);
}
