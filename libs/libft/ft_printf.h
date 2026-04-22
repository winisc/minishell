/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:33:53 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/28 20:15:14 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(size_t nbr);
int		ft_putnbr_hex(unsigned int nbr, int to);
int		ft_putnbr_u(unsigned int nbr);
int		ft_putnbr_pointer(size_t nbr);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);

#endif