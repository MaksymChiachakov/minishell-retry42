/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:32:17 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/05 17:26:47 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_sorted(char **env)
{
	int		i[2];
	char	*temp;

	env = ft_copy_env(env);
	if (!env)
		return ;
	i[0] = -1;
	while (env[++i[0]])
	{
		i[1] = i[0];
		while (env[++i[1]])
		{
			if (ft_strcmp(env[i[0]], env[i[1]]) > 0)
			{
				temp = env[i[0]];
				env[i[0]] = env[i[1]];
				env[i[1]] = temp;
			}
		}
	}
	i[0] = -1;
	while (env[++i[0]])
		ft_printf("declare -x %s\n", env[i[0]]);
	free_env(env);
}

static int	add_or_update_env(char *arg, t_env *shell)
{
	char	*equals;
	char	*key;
	char	*existing;

	equals = ft_strchr(arg, '=');
	if (!equals)
	{
		if (!is_valid_env_name(arg))
			return (print_error("export", arg, "not a valid identifier"), 1);
		existing = get_env_value(arg, shell);
		if (existing)
			return (free(existing), 0);
		return (set_env_value(arg, "", shell), 0);
	}
	key = ft_substr(arg, 0, equals - arg);
	if (!key)
		return (1);
	if (!is_valid_env_name(key))
	{
		print_error("export", arg, "not a valid identifier");
		return (free(key), 1);
	}
	set_env_value(key, equals + 1, shell);
	return (free(key), 0);
}

int	ft_export(t_command *cmd, t_env *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (print_env_sorted(shell->envp), 0);
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (add_or_update_env(cmd->args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
