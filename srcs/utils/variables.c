/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:48:34 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/05 18:11:26 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_var(t_env *e, char *name, int len)
{
	char	*temp;
	char	*result;
	int		i;

	temp = malloc(len + 1);
	ft_strncpy(temp, name, len);
	temp[len] = '\0';
	i = 0;
	while (e->envp[i])
	{
		if (ft_strncmp(e->envp[i], temp, len) == 0 && e->envp[i][len] == '=')
		{
			result = ft_strdup(e->envp[i] + len + 1);
			free(temp);
			return (result);
		}
		i++;
	}
	return (free(temp), NULL);
}
