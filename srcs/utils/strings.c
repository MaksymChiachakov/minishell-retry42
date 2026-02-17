/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:57:41 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/14 14:01:57 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_shell_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	ft_concat(char **dst, char *src, int src_len)
{
	char	*new;
	int		dst_len;
	int		capacity;

	if (src_len == -1)
		src_len = ft_strlen(src);
	capacity = 8;
	while ((*dst)[capacity - 1])
		capacity *= 2;
	dst_len = ft_strlen(*dst);
	if (dst_len + src_len + 1 > capacity)
	{
		while (dst_len + src_len + 1 > capacity)
			capacity *= 2;
		new = malloc(capacity);
		if (!new)
			return (-1);
		new[capacity - 1] = '\0';
		ft_memcpy(new, *dst, dst_len);
		free(*dst);
		*dst = new;
	}
	ft_memcpy(*dst + dst_len, src, src_len);
	(*dst)[dst_len + src_len] = '\0';
	return (capacity);
}

char	*join_path(char *dir, char *file)
{
	char	*path;
	int		len;

	len = ft_strlen(dir) + ft_strlen(file) + 2;
	path = ft_calloc(sizeof(char), len);
	if (path == NULL)
		return (NULL);
	ft_strlcat(path, dir, len);
	ft_strlcat(path, "/", len);
	ft_strlcat(path, file, len);
	return (path);
}

void	free_split(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}
