/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_var_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/21 23:57:01 by lguerbig         ###   ########.fr       */
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
		}
		if (!token.value[j])
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

static char **add_env_var(char **envp,const char *value)
{
	char	**new_var;
	
	new_var = (char **)ft_calloc(2, sizeof(char *));
	if (!new_var) {
		perror("calloc failed");
		return NULL;
	}
	new_var[0] = ft_strdup(value);
	envp = tab_join_and_free(envp, new_var); //rip protection
	return envp;
}

void	test_var_expand(char **envp)
{
	size_t	test_number;
	t_token token;

	start_test("environement variable expansion");
	test_number = 1;

	/*--- test 1 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$PATH", NULL));
	expand_env_var(&token, envp);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", getenv("PATH"), NULL);
	token_clear(token);

	/*--- test 2 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$test", NULL));
	expand_env_var(&token, envp);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", NULL);
	token_clear(token);

	char **env = add_env_var(NULL,"test=oui   non");

	/*--- test 3 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$test", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "oui", "non", NULL);
	token_clear(token);

	/*--- test 4 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "\'$test\'", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "\'$test\'", NULL);
	token_clear(token);

	/*--- test 5 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "\"$test\"", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "\"oui   non\"", NULL);
	token_clear(token);

	/*--- test 6 ---*/
	token = token_create(TOKEN_CMD, built_tab("echo", "$test\"$test\"", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "oui", "non\"oui   non\"", NULL);
	token_clear(token);

	env = add_env_var(env,"a=e");
	env = add_env_var(env,"b=c");
	env = add_env_var(env,"c=h");
	env = add_env_var(env,"d=o");

	/*--- test 7 ---*/
	token = token_create(TOKEN_CMD, built_tab("$a$b$c$d", "bonjour", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "echo", "bonjour", NULL);
	token_clear(token);
	
	env = add_env_var(env,"e='e'");

	/*--- test 8 ---*/
	token = token_create(TOKEN_CMD, built_tab("$e$b$c$d", "bonjour", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "\"'\"e\"'\"cho", "bonjour", NULL);
	token_clear(token);

	env = add_env_var(env,"f='e '");

	/*--- test 9 ---*/
	token = token_create(TOKEN_CMD, built_tab("$f$b$c$d", "bonjour", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "\"'\"e", "\"'\"cho", "bonjour", NULL);
	token_clear(token);

	/*--- test 10 ---*/
	token = token_create(TOKEN_CMD, built_tab("$", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "$", NULL);
	token_clear(token);

	/*--- test 11 ---*/
	token = token_create(TOKEN_CMD, built_tab("$$test", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_CMD, "$oui", "non", NULL);
	token_clear(token);

	/*--- test 12 ---*/
	token = token_create(TOKEN_REDIR, built_tab("<oui", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_REDIR, "<oui", NULL);
	token_clear(token);
	
	/*--- test 13 ---*/
	token = token_create(TOKEN_REDIR, built_tab("<$test", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_REDIR, "<oui", "non", NULL);
	token_clear(token);

	/*--- test 14 ---*/
	token = token_create(TOKEN_REDIR, built_tab("<<\'$test\'", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_REDIR, "<<\'$test\'", NULL);
	token_clear(token);

	/*--- test 15 ---*/
	token = token_create(TOKEN_REDIR, built_tab("<<$test", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_REDIR, "<<$test", NULL);
	token_clear(token);

	/*--- test 16 ---*/
	token = token_create(TOKEN_REDIR, built_tab("<$test\"\'\"", NULL));
	expand_env_var(&token, env);
	assert_equal_token(token, &test_number, TOKEN_REDIR, "<oui", "non\"\'\"", NULL);
	token_clear(token);

	ft_clean_matrix((void **)env);
}
