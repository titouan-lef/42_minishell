/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_to_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:49:53 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/04 12:37:27 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

/*
* Warninig: assert_equal_i compare int
*/
static void	execution_long_long(long long start, long long end, long long max, size_t *test_number)
{
	int				status;
	long long		result;
	char			str[25];

	for (long long i = start; i < end; ++i)
	{
		sprintf(str, "%lld", i);
		result = (long long)ft_to_number(str, &status, max);
		if (result != i || status)
		{
			assert_equal_i(i, result, test_number);
			assert_equal_i(0, status, test_number);
		}
	}
	sprintf(str, "%lld", end);
	result = (long long)ft_to_number(str, &status, max);
	assert_equal_i(end, result, test_number);
	assert_equal_i(0, status, test_number);
}

static void	execution_int(int start, int end, long long max, size_t *test_number)
{
	int		status;
	int		result;
	char	str[25];

	for (int i = start; i < end; ++i)
	{
		sprintf(str, "%d", i);
		result = (int)ft_to_number(str, &status, max);
		if (result != i || status)
		{
			assert_equal_i(i, result, test_number);
			assert_equal_i(0, status, test_number);
		}
	}
	sprintf(str, "%d", end);
	result = (int)ft_to_number(str, &status, max);
	assert_equal_i(end, result, test_number);
	assert_equal_i(0, status, test_number);
}

static void	test_to_long_long_error(size_t *test_number)
{
	int		status;
	char	str[6][25] = {
		"-20v",
		"",
		"--10",
		"9223372036854775808",
		"-9223372036854775809",
		"18446744073709551615"
	};

	for (int i = 0; i < 6; ++i)
	{
		ft_to_number(str[i], &status, INT_MAX);
		assert_true(status, test_number);
	}
}

static void	test_to_long_long(size_t *test_number)
{
	execution_long_long(LLONG_MIN, LLONG_MIN + 20, LLONG_MAX, test_number);
	execution_long_long(-20, 20, LLONG_MAX, test_number);
	execution_long_long(LLONG_MAX - 20, LLONG_MAX, LLONG_MAX, test_number);
}

static void	test_to_int_error(size_t *test_number)
{
	int		status;
	char	str[6][25] = {
		"-20v",
		"",
		"--10",
		"2147483648",
		"-2147483649",
		"18446744073709551615"
	};

	for (int i = 0; i < 6; ++i)
	{
		ft_to_number(str[i], &status, INT_MAX);
		assert_true(status, test_number);
	}
}

static void	test_to_int(size_t *test_number)
{
	execution_int(INT_MIN, INT_MIN + 20, INT_MAX, test_number);
	execution_int(-20, 20, INT_MAX, test_number);
	execution_int(INT_MAX - 20, INT_MAX, INT_MAX, test_number);
}

void	test_to_number(void)
{
	size_t	test_number = 1;
	start_test("ft_to_number");

	test_to_int(&test_number);
	test_to_int_error(&test_number);
	test_to_long_long(&test_number);
	test_to_long_long_error(&test_number);
}