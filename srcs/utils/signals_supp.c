/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_supp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:26:36 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/18 18:17:30 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	setup_signals();
}
