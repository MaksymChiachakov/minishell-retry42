/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:32:06 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/05 20:33:43 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	n_option(char *argv);

int	echo_build(t_command *cmd, char **av)
{
	int	new_line;
	int	i;

	if (!av)
		return (1);
	new_line = 1;
	i = 1;
	while (av[i] && n_option(av[i]))
	{
		new_line = 0;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], cmd->outfd);
		if (av[i + 1])
			ft_putstr_fd(" ", cmd->outfd);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", cmd->outfd);
	return (0);
}

static int	n_option(char *argv)
{
	int	i;

	if (!argv || argv[0] != '-')
		return (0);
	i = 1;
	if (argv[i] == '\0')
		return (0);
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
