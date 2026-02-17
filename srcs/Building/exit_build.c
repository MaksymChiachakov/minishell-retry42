/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:13:26 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/10 17:35:25 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	calculate_exit_code(char *arg)
{
	int	exit_code;

	exit_code = ft_atoi(arg);
	exit_code = exit_code & 0xFF;
	if (exit_code & 0x80)
		exit_code |= 0xFFFFFF00;
	return (exit_code);
}

int	ft_exit(t_command *cmd, t_env *env)
{
	char	*arg;

	arg = cmd->args[1];
	if (isatty(STDIN_FILENO))
		write(cmd->outfd, "exit\n", 5);
	if ((arg && cmd->args[2]) & (arg && !is_numeric(arg)))
	{
		env->should_exit = true;
		return (print_error("exit", NULL, "too many arguments"), 2);
	}
	env->should_exit = true;
	if (arg && cmd->args[2])
		return (print_error("exit", NULL, "too many arguments"), 1);
	if (arg && !is_numeric(arg))
		return (print_error("exit", arg, "numeric argument required"), 2);
	else if (arg)
		return (calculate_exit_code(arg));
	else
		return (env->code_exit);
}
