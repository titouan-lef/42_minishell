/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:23:02 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:52:26 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H
# include <stdlib.h>
# include <unistd.h>

ssize_t	ft_printf(const char *format, ...);
ssize_t	ft_printf_fd(int fd, const char *format, ...);
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putchar_error(char c);
ssize_t	ft_putchar(char c);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_putstr_error(char *s);
ssize_t	ft_putstr(char *s);
ssize_t	ft_putendl_fd(char *s, int fd);
ssize_t	ft_putendl_error(char *s);
ssize_t	ft_putendl(char *s);
ssize_t	ft_putnbr_fd(long n, int fd);
ssize_t	ft_putnbr_error(long n);
ssize_t	ft_putnbr(long n);
ssize_t	ft_putnbr_base_fd(long n, char *base, int fd);
ssize_t	ft_putnbr_base_error(long n, char *base);
ssize_t	ft_putnbr_base(long n, char *base);
ssize_t	ft_putunbr_fd(unsigned long n, int fd);
ssize_t	ft_putunbr_error(unsigned long n);
ssize_t	ft_putunbr(unsigned long n);
ssize_t	ft_putunbr_base_fd(unsigned long n, char *base, int fd);
ssize_t	ft_putunbr_base_error(unsigned long n, char *base);
ssize_t	ft_putunbr_base(unsigned long n, char *base);

#endif