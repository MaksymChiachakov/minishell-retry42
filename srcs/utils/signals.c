/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:06:01 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/06 19:53:40 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// volatile sig_atomic_t	g_signal = 0;

// Обробка Ctrl+C (SIGINT) - інтерактивний режим
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_signal = 1;
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_pipe;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
	sa_pipe.sa_handler = SIG_IGN;
	sigemptyset(&sa_pipe.sa_mask);
	sa_pipe.sa_flags = 0;
	sigaction(SIGPIPE, &sa_pipe, NULL);
}

// Налаштування сигналів для неінтерактивного режиму (скрипти)
void	setup_signals_noninteractive(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// Основна функція налаштування сигналів
void	setup_signals(void)
{
	if (isatty(STDIN_FILENO))
		setup_signals_interactive();
	else
		setup_signals_noninteractive();
}

void	handle_child_signals(void)
{
	sigset_t	empty;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	sigemptyset(&empty);
	sigprocmask(SIG_SETMASK, &empty, NULL);
}
