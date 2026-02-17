/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:25:24 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/08 18:04:35 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putunbr(unsigned int n)
{
	char	c;

	if (n >= 10)
		ft_putunbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

static int	ft_ulen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	ft_putunbr(n);
	return (ft_ulen(n));
}
