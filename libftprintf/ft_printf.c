/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:42:49 by vabertau          #+#    #+#             */
/*   Updated: 2023/12/01 13:15:08 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_print_el(char format, va_list ap)
{
	if (format == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		return (1);
	}
	if (format == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (format == 'p')
		return (ft_putptr(va_arg(ap, unsigned long long)));
	if (format == 'd' || format == 'i')
		return (ft_putnbrlen_fd(va_arg(ap, unsigned long long), 1));
	if (format == 'u')
		return (ft_putunslen_fd(va_arg(ap, unsigned long long), 1));
	if (format == 'x')
		return (ft_puthexa2(va_arg(ap, unsigned long long),
				"0123456789abcdef"));
	if (format == 'X')
		return (ft_puthexa2(va_arg(ap, unsigned long long),
				"0123456789ABCDEF"));
	if (format == '%')
	{
		write (1, "%", 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		ret;
	va_list	ap;

	i = 0;
	ret = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ret += ft_print_el(str[i + 1], ap);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			ret++;
		}
		i++;
	}
	va_end(ap);
	return (ret);
}

/* #include <stdio.h> */

/*=============== TEST FT_PUT_HEXA ==================*/
/*
int	main(void)
{
	unsigned long long ptr = 15;
	ft_puthexa(ptr, "0123456789abcdef");
}
*/
/*
int	main(void)
{
	//char s[] = "test";
	char c;

	printf("ret ft = %i\n", ft_printf("Number ft: %u\n", -1));
        printf("ret orig = %i\n\n", printf("Number or: %u\n", -1));

	printf("ret ft = %i\n", ft_printf("test ptr 0 ft %p\n", (char*)0));
	printf("ret orig = %i\n\n", printf("test ptr 0 or %p\n", (char*)0));

	printf("nb hexa %i", ft_puthexa((unsigned long long)&c, "0123456789abcdef"));

	ft_printf("return ft = %i\n", ft_printf("char: %c\n", 'c'));
        printf("return original = %i\n\n", printf("char: %c\n", 'c'));

	//ft_printf("return ft = %i\n", ft_printf("str: %s\n", (char*)0));
	//printf("return original = %i\n\n", printf("str: %s\n", (char*)0));
	
	ft_printf("return ft = %i\n", ft_printf("ptr: %p\n", &c));
	printf("return original= %i\n\n", printf("ptr: %p\n", &c));

	printf("ret ft = %i\n", ft_printf("Number ft: %d\n", -1));
	printf("ret orig = %i\n\n", printf("Number or: %d\n", -1));

	ft_printf("return ft = %i\n", ft_printf("Number: %x\n", 1256));
        printf("return original = %i\n\n", printf("Number: %x\n", 1256));

	ft_printf("Number: %X\n", 1256);
	printf("printf number : %X\n\n", 1256);

	ft_printf("Number: %%\n");
	printf("printf number : %%\n\n");

	//ft_putptr(&s);
}*/
