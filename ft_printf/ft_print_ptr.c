/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:34:20 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/08 18:04:09 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex_ptr(unsigned long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_puthex_ptr(n / 16);
	write(1, &base[n % 16], 1);
}

static int	ft_hexlen_ptr(unsigned long n)
{
	int	len;

	len = 1;
	while (n >= 16)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_print_ptr(void *ptr)
{
	unsigned long	addr;
	int				len;

	len = 0;
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	len += 2;
	if (addr == 0)
		len += write(1, "0", 1);
	else
	{
		ft_puthex_ptr(addr);
		len += ft_hexlen_ptr(addr);
	}
	return (len);
}
