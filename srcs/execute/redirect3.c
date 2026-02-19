/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:29:25 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/19 15:08:40 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/* heredoc support */
int	hs(t_env *e, char *l, struct sigaction *s, int f[2])
{
	free(l);
	close(f[0]);
	close(f[1]);
	e->code_exit = 130;
	g_signal = 0;
	write(1, "\n", 1);
	sigaction(SIGINT, s, NULL);
	return (-1);
}

void	heredoc_supp_sec(char *line, int fds[2])
{
	write(fds[1], line, ft_strlen(line));
	write(fds[1], "\n", 1);
	free(line);
}

int	test_if(int fds[2], t_token *eof, t_env *e)
{
	if (pipe(fds) == -1)
		return (system_error(e, "minishell: pipe: "));
	*eof = get_next_token(e);
	if ((*eof).kind != TOKEN_WORD)
		return (syntax_error(e, *eof));
	return (0);
}