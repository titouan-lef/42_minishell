/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:07:45 by tle-floc          #+#    #+#             */
/*   Updated: 2024/12/15 11:00:44 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

/*---Colors---*/
# define NO_COLOR "\033[0m"
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"

/*---Test functions---*/
void	start_test(char *name);
void	assert_equal_s(char *expected, char *result, size_t *i);
void	assert_equal_i(int expected, int result, size_t *i);
void	assert_true(int result, size_t *i);
void	assert_false(int result, size_t *i);
void	assert_equal_b(int expected, int result, size_t *i);
void	assert_null(void *result, size_t *i);
void	assert_not_null(void *result, size_t *i);

#endif
