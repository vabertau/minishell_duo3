/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:56:22 by vabertau          #+#    #+#             */
/*   Updated: 2023/11/27 12:50:22 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

int	ft_putptr(unsigned long long ptr);
int	ft_puthexa(unsigned long long ptr, char *table);
int	ft_puthexa2(unsigned int nb, char *table);
int	ft_printf(const char *str, ...);
int	ft_putstr(char *s);
int	ft_putnbrlen_fd(int n, int fd);
int	ft_putunslen_fd(unsigned int n, int fd);

#endif
