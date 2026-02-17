/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:32:25 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/04 10:42:00 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_command *cmd, t_env *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (0);
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_env_name(cmd->args[i]))
		{
			print_error("unset", cmd->args[i], "not a valid identifier");
			ret = 1;
		}
		else
			remove_env_var(cmd->args[i], shell);
		i++;
	}
	return (ret);
}
