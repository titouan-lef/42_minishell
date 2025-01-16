/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pathname_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/14 17:52:42 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static char	**built_tab(char* first, ...)
{
	char	**tab;
	va_list	args;
	va_list	args_cpy;
	int		nb_args;
	int		j;

	va_start(args, first);
	nb_args = 0;
	va_copy(args_cpy, args);
	while(va_arg(args_cpy, char *))
		++nb_args;
	va_end(args_cpy);
	tab = ft_calloc(nb_args + 2, sizeof(char *));
	if (!tab)
	{
		ft_printf_fd(2, "malloc errro");
		return (NULL);
	}
	j = 0;
	tab[j++] = ft_strdup(first); //rip protection
	while (j <= nb_args)
		tab[j++] = ft_strdup((char *)va_arg(args, char *)); //rip protection
	va_end(args);
	return (tab);
}

static void	assert_equal_token(t_token token, size_t *i, ...)
{
	char			*expected_value;
	t_token_name	expected_name;
	va_list			args;
	va_list			args_cpy;
	int				nb_args;
	int				j;

	va_start(args, i);
	nb_args = 0;
	va_copy(args_cpy, args);
	while(va_arg(args_cpy, char *))
		++nb_args;
	va_end(args_cpy);
	expected_name = (t_token_name)va_arg(args, t_token_name);
	if (expected_name != token.name)
	{
		print_ko(enum_to_str(expected_name), enum_to_str(token.name), i);
		va_end(args);
		return;
	}
	j = 0;
	while (j < nb_args - 1)
	{
		expected_value = (char *)va_arg(args, char *);
		if (!token.value)
		{
			print_ko(expected_value, "(null)", i);
			va_end(args);
			return ;
		}if (!token.value[j])
		{
			print_ko(expected_value, token.value[j], i);
			va_end(args);
			return ;
		}
		if (ft_strcmp(token.value[j], expected_value))
		{
			print_ko(expected_value, token.value[j], i);
			va_end(args);
			return ;
		}
		j++;
	}
	va_end(args);
	if (token.value[j])
		print_ko("(null)", token.value[j], i);
	else
		print_ok(i);
}

void	test_pathname_expand(void)
{
	size_t	test_number;
	t_token token;

	start_test("pathname expansion");
	test_number = 1;

	/*--- test 1 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "*pathname*", NULL));
	expand_wildcard(&token);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "test_pathname_expansion.c", NULL);
	token_clear(token);

	/*--- test 2 ---*/ //need sorting
	token = token_create(TOKEN_CMD, built_tab("echo", "tester*", NULL));
	expand_wildcard(&token);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "tester.c", "tester.h", NULL);
	token_clear(token);

	/*--- test 3 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "*.a", "*.h", NULL));
	expand_wildcard(&token);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "minishell.a", "tester.h", NULL);
	token_clear(token);

	//check "echo *" when directory is empty, waiting for cd for mor testr
}
