/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:07:45 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 19:01:56 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>

/*---Types----*/

typedef struct s_out
{
	int	out;
	int	err;
	int	save_out;
	int	save_err;
}				t_out;

/*---colors---*/
# define NO_COLOR "\033[0m"
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"

/*---test functions---*/
void	start_test(char *name);
void	print_ko(char* expected, char *result, size_t *i);
void	print_ok(size_t *i);
void	assert_equal_s(char *expected, char *result, size_t *i);
int		redirect_outputs(t_out *outputs);
void	set_normal_outputs(t_out *outputs);
void	assert_equal_out( char *expected, size_t *i);
void	assert_equal_err(char *expected, size_t *i);
void	assert_equal_i(int expected, int result, size_t *i);
void	assert_true(int result, size_t *i);
void	assert_false(int result, size_t *i);
void	assert_equal_b(int expected, int result, size_t *i);
void	assert_null(void *result, size_t *i);
void	assert_not_null(void *result, size_t *i);

#endif
