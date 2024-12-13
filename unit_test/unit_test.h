/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:07:45 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/15 10:52:00 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

void	start_test(char *name);
void	assert_equal_s(char *expected, char *result, size_t *i);
void	assert_equal_i(int expected, int result, size_t *i);
void	assert_true(int result, size_t *i);
void	assert_false(int result, size_t *i);
void	assert_equal_b(int expected, int result, size_t *i);
void	assert_null(void *result, size_t *i);
void	assert_not_null(void *result, size_t *i);

#endif
