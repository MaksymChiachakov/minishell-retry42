/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:52:31 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/04 10:52:34 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcat(char *dst, const char *src)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	if (!dst)
		return (0);
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = 0;
	while (src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
