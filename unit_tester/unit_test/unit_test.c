/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:16:40 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/14 20:48:58 by lguerbig         ###   ########.fr       */
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

int	redirect_outputs(t_out *outputs)
{
	outputs->out = open("cout.log", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (-1 == outputs->out)
	{
		perror("opening cout.log");
		exit(255);
	}
	outputs->err = open("cerr.log", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (-1 == outputs->err)
	{
		perror("opening cerr.log");
		exit(255);
	}
	fflush(stdout);
	fflush(stderr);
	outputs->save_out = dup(fileno(stdout));
	outputs->save_err = dup(fileno(stderr));
	if (-1 == dup2(outputs->out, fileno(stdout)))
	{
		perror("cannot redirect stdout");
		exit(255);
	}
	if (-1 == dup2(outputs->err, fileno(stderr)))
	{
		perror("cannot redirect stderr");
		exit(255);
	}
	return (0);
}

void	set_normal_outputs(t_out *outputs)
{
	fflush(stdout);
	close(outputs->out);
	fflush(stderr);
	close(outputs->err);

	dup2(outputs->save_out, fileno(stdout));
	dup2(outputs->save_err, fileno(stderr));

	close(outputs->save_out);
	close(outputs->save_err);
}

void	start_test(char *name)
{
	printf("\n\ntest %s :\n", name);
}

void	print_ko(char* expected, char *result, size_t *i)
{
	printf(RED);
	printf("\n====================== %zu.KO ======================\n", *i);
	printf("expected : '%s'\n", expected);
	printf("result : '%s'\n", result);
	printf("==================================================\n");
	printf(NO_COLOR);
	*i += 1;
}

void	print_ok(size_t *i)
{
	printf(GREEN);
	printf("%zu.OK ", *i);
	printf(NO_COLOR);
	*i += 1;
}

void	assert_equal_s(char *expected, char *result, size_t *i)
{
	if (strcmp(expected, result) == 0)
		print_ok(i);
	else
		print_ko(expected, result, i);
}

static void	assert_equal_output(char *expected, size_t *i, char *file)
{
	char	*result;
	int		fd;

	fd = open(file, O_RDONLY);
	result = calloc(10000,sizeof(char));
	if (!result)
	{
		perror("malloc failed: assert_equal_output");
		exit(1);
	}
	read(fd, result, 10000);
	close(fd);
	unlink(file);
	if (strcmp(expected, result) == 0)
		print_ok(i);
	else
		print_ko(expected, result, i);
	free(result);
}

void	assert_equal_out(char *expected, size_t *i)
{
	assert_equal_output(expected, i, "cout.log");
}

void	assert_equal_err(char *expected, size_t *i)
{
	assert_equal_output(expected, i, "cerr.log");
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