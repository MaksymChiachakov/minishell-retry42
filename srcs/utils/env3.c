/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:36:21 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/19 14:57:41 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	set_env_value_supp(char *new_var, t_env *env)
{
	char	**new_env;
	int		i;	
	int		size;

	size = ft_arrlen(env->envp) + 2;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	i = -1;
	while (env->envp[++i])
		new_env[i] = env->envp[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(env->envp);
	env->envp = new_env;
}

void	set_env_value(char *key, const char *value, t_env *env)
{
	char	*new_var;
	size_t	key_len;

	key_len = ft_strlen(key);
	new_var = malloc(key_len + ft_strlen(value) + 2);
	if (!new_var)
		return ;
	ft_strcpy(new_var, key);
	new_var[key_len] = '=';
	ft_strcpy(new_var + key_len + 1, (char *)value);
	if (update_env_value(new_var, key_len, env))
		return ;
	set_env_value_supp(new_var, env);
}

void	init_default_env(t_env *env)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		set_env_value("PWD", cwd, env);
	shlvl_str = get_env_value("SHLVL", env);
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		free(shlvl_str);
	}
	else
		shlvl = 0;
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	set_env_value("SHLVL", new_shlvl, env);
	free(new_shlvl);
	set_env_value("_", "./minishell", env);
}
