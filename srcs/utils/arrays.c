/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:30:06 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/14 14:36:08 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	ft_append(char ***list, char *item)
{
	char	**new;
	int		len;

	if (!item)
		return ;
	len = ft_arrlen(*list);
	if (len == 0 && ft_strlen(item) == 0)
		return (free(item));
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
	{
		free(item);
		return ;
	}
	ft_memcpy(new, *list, len * sizeof(char *));
	new[len] = item;
	free(*list);
	*list = new;
}
