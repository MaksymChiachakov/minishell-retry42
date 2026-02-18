/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:14:43 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/18 13:27:38 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static char	**create_minimal_env(void)
{
	char	**minimal_env;
	char	cwd[4096];
	char	*pwd;
	
	minimal_env = malloc(sizeof(char *) * 4);
	if (!minimal_env)
		return (NULL);
	if (getcwd(cwd, sizeof(cwd)))
		pwd = ft_strjoin("PWD=", cwd);
	else
		pwd = ft_strdup("PWD=/");
	minimal_env[0] = pwd;
	minimal_env[1] = ft_strdup("SHLVL=0");
	minimal_env[2] = ft_strdup("_=/usr/bin/env");
	minimal_env[3] = NULL;
	return (minimal_env);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**ft_copy_env(char **env)
{
	char	**new_env;
	int		count;
	int		i;

	if (!env || !env[0])
		return (create_minimal_env());
	count = ft_arrlen(env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (create_minimal_env());
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (free(new_env), create_minimal_env());
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

char	*get_env_value(char *key, t_env *env)
{
	int		i;
	char	*env_key;
	char	*value;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strchr(env->envp[i], '='))
		{
			env_key = ft_substr(env->envp[i], 0, ft_strchr(env->envp[i], '=')
					- env->envp[i]);
			if (ft_strcmp(env_key, key) == 0)
			{
				value = ft_strdup(ft_strchr(env->envp[i], '=') + 1);
				return (free(env_key), value);
			}
			free(env_key);
		}
		i++;
	}
	return (NULL);
}

int	update_env_value(char *var, int key_len, t_env *env)
{
	int		i;

	i = -1;
	while (env->envp[++i])
	{
		if (ft_strncmp(env->envp[i], var, key_len + 1) == 0)
		{
			free(env->envp[i]);
			env->envp[i] = var;
			return (1);
		}
	}
	return (0);
}

void	set_env_value(char *key, const char *value, t_env *env)
{
	int		i;
	char	*new_var;
	char	**new_env;
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
	new_env = calloc(ft_arrlen(env->envp) + 2, sizeof(char *));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	i = -1;
	while (env->envp[++i])
		new_env[i] = env->envp[i];
	new_env[i] = new_var;
	free(env->envp);
	env->envp = new_env;
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