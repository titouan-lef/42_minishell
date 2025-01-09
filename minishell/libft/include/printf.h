/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:44:21 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:51:40 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "libft.h"
# include <stdarg.h>

ssize_t	ft_printf_char(va_list arg, int fd);
ssize_t	ft_printf_string(va_list arg, int fd);
ssize_t	ft_printf_percent(int fd);
ssize_t	ft_printf_nbr(va_list arg, int fd);
ssize_t	ft_printf_unbr(va_list arg, int fd);
ssize_t	ft_printf_unbr_lowhexa(va_list arg, int fd);
ssize_t	ft_printf_unbr_uphexa(va_list arg, int fd);
ssize_t	ft_printf_address(va_list arg, int fd);
ssize_t	ft_printf_error(char c, int fd);

#endif