/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:45:58 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/08 18:26:58 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_handler(const char *format, int *i, va_list args)
{
	if (format[*i] == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (format[*i] == 's' || format[*i] == '-' || format[*i] == '.'
		|| (format[*i] >= '0' && format[*i] <= '9'))
		return (ft_print_str(format, i, args));
	else if (format[*i] == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (format[*i] == 'd' || format[*i] == 'i')
		return (ft_print_nbr(va_arg(args, int)));
	else if (format[*i] == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (format[*i] == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (format[*i] == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (format[*i] == '%')
		return (write(1, "%", 1));
	return (0);
}
