/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:14:23 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/13 17:16:18 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *arg, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	flag_error(t_env *e, char *cmd, char *arg, char *error)
{
	print_error(cmd, arg, error);
	e->should_exit = true;
	e->code_exit = 2;
}

void	check_execuable_error(char *bin)
{
	struct stat	st;

	if (stat(bin, &st) != 0)
	{
		print_error(bin, NULL, "No such file or directory");
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_error(bin, NULL, "Permission denied");
		exit(126);
	}
	if (access(bin, X_OK) != 0)
	{
		print_error(bin, NULL, "Permission denied");
		exit(126);
	}
}
