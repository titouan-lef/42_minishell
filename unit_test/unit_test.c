/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:16:40 by tle-floc          #+#    #+#             */
/*   Updated: 2024/10/15 16:04:44 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

static size_t	number_digits(int n)
{
	size_t	size;

	n = n / 10;
	size = 1;
	while (n != 0)
	{
		n = n / 10;
		++size;
	}
	return (size);
}

static void	write_numbers(unsigned int nbp, char *str, size_t size)
{
	--size;
	str[size] = '\0';
	while (size > 0)
	{
		--size;
		str[size] = nbp % 10 + '0';
		nbp = nbp / 10;
	}
}

static char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	nbp;
	size_t			size;
	size_t			offset;

	nbp = n;
	offset = 0;
	if (n < 0)
	{
		nbp = -n;
		++offset;
	}
	size = number_digits(n) + offset + 1;
	result = (char *)malloc(size * sizeof(char));
	if (!result)
		return (NULL);
	write_numbers(nbp, result + offset, size - offset);
	if (offset)
		result[0] = '-';
	return (result);
}

void	start_test(char *name)
{
	printf("\n\ntest %s :\n", name);
}

void	print_ko(char* expected, char *result, size_t *i)
{
	printf("\x1B[31m");
	printf("\n====================== %zu.KO ======================\n", *i);
	printf("expected : %s\n", expected);
	printf("result : %s\n", result);
	printf("==================================================\n");
	printf("\x1B[0m");
	*i += 1;
}

void	print_ok(size_t *i)
{
	printf("\x1B[32m");
	printf("%zu.OK ", *i);
	printf("\x1B[0m");
	*i += 1;
}

void	assert_equal_s(char *expected, char *result, size_t *i)
{
	if (strcmp(expected, result) == 0)
		print_ok(i);
	else
		print_ko(expected, result, i);
}

void	assert_equal_i(int expected, int result, size_t *i)
{
	char	*str_expected;
	char	*str_result;
	if (expected == result)
		print_ok(i);
	else
	{
		str_expected = ft_itoa(expected);
		str_result = ft_itoa(result);
		print_ko(str_expected, str_result, i);
		free(str_expected);
		free(str_result);
	}
}

void	assert_true(int result, size_t *i)
{
	if (result)
		print_ok(i);
	else
		print_ko("true", "false", i);
}

void	assert_false(int result, size_t *i)
{
	if (!result)
		print_ok(i);
	else
		print_ko("false", "true", i);
}

void	assert_equal_b(int expected, int result, size_t *i)
{
	if (expected)
		assert_true(result, i);
	else
		assert_false(result, i);
}

void	assert_null(void *result, size_t *i)
{
	if (result)
		print_ko("null", "not null", i);
	else
		print_ok(i);
}

void	assert_not_null(void *result, size_t *i)
{
	if (result)
		print_ok(i);
	else
		print_ko("not null", "null", i);
}