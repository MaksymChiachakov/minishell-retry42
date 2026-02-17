/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:09:08 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/06 16:48:15 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_name(char *name)
{
	int	i;

	if (!name || !*name || ft_isdigit(*name))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	rmv_env3(char *key, t_env *env, int count, size_t key_len)
{
	int		j;
	int		i;
	size_t	var_len;

	i = 0;
	j = 0;
	var_len = 0;
	while (i < count)
	{
		var_len = ft_strlen(env->envp[i]);
		if (!(key_len < var_len
				&& ft_strncmp(env->envp[i], key, key_len) == 0
				&& env->envp[i][key_len] == '='))
		{
			env->new_env[j] = env->envp[i];
			j++;
		}
		else
			free(env->envp[i]);
		i++;
	}
	env->new_env[j] = NULL;
	free(env->envp);
	env->envp = env->new_env;
}

void	rmv_env2(char *key, t_env *env, int count, size_t key_len)
{
	int		new_count;
	int		i;
	size_t	var_len;

	new_count = 0;
	i = 0;
	while (i < count)
	{
		var_len = ft_strlen(env->envp[i]);
		if (!(key_len < var_len
				&& ft_strncmp(env->envp[i], key, key_len) == 0
				&& env->envp[i][key_len] == '='))
			new_count++;
		i++;
	}
	env->new_env = malloc(sizeof(char *) * (new_count + 1));
	if (!env->new_env)
		return ;
	rmv_env3(key, env, count, key_len);
}

void	remove_env_var(char *key, t_env *env)
{
	int		count;
	size_t	key_len;

	if (!key || !env || !env->envp)
		return ;
	count = 0;
	while (env->envp[count])
		count++;
	if (count == 0)
		return ;
	key_len = ft_strlen(key);
	rmv_env2(key, env, count, key_len);
}
