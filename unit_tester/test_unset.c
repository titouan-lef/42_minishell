/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/23 12:42:19 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static void	assert_equal_tab(char **tab, size_t *i, ...)
{
	char			*expected_value;
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
	j = 0;
	while (j < nb_args)
	{
		expected_value = (char *)va_arg(args, char *);
		if (!tab[j])
		{
			print_ko(expected_value, tab[j], i);
			va_end(args);
			return ;
		}
		if (ft_strcmp(tab[j], expected_value))
		{
			print_ko(expected_value, tab[j], i);
			va_end(args);
			return ;
		}
		j++;
	}
	va_end(args);
	if (tab[j])
		print_ko("(null)", tab[j], i);
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
	new_var[0] = ft_strdup(value); //rip protection
	envp = tab_join_and_free(envp, new_var); //rip protection
	return envp;
}

void	test_unset(void)
{
	size_t	test_number;
	char	**cmd;

	start_test("unset");
	test_number = 1;

	char **env = add_env_var(NULL,"test=test");

	/*--- test 1 ---*/
	cmd = built_tab("unset", "test", NULL);
	unset(cmd, &env);
	assert_equal_tab(env, &test_number, NULL);
	ft_clean_matrix((void **)cmd);

	env = add_env_var(env,"test=test");
	env = add_env_var(env,"test2=test");

	/*--- test 2 ---*/
	cmd = built_tab("unset", "test2", NULL);
	unset(cmd, &env);
	assert_equal_tab(env, &test_number, "test=test", NULL);
	ft_clean_matrix((void **)cmd);

	env = add_env_var(env,"test2=test");
	env = add_env_var(env,"bonjour=test");

	/*--- test 3 ---*/
	cmd = built_tab("unset", "test", NULL);
	unset(cmd, &env);
	assert_equal_tab(env, &test_number, "test2=test", "bonjour=test", NULL);
	ft_clean_matrix((void **)cmd);

	/*--- test 4 ---*/
	cmd = built_tab("unset", "test2", "bonjour", NULL);
	unset(cmd, &env);
	assert_equal_tab(env, &test_number, NULL);
	ft_clean_matrix((void **)cmd);

	/*--- test 5 ---*/
	cmd = built_tab("unset", "test2", "bonjour", "bwebfpwk", NULL);
	unset(cmd, &env);
	assert_equal_tab(env, &test_number, NULL);
	ft_clean_matrix((void **)cmd);

	env = add_env_var(env,"test=test");

	/*--- test 6 ---*/
	cmd = built_tab("unset", "erg hkfbpergreh", "gerjkg wibfgw", "bwebfpwk", NULL);
	unset(cmd, &env);
	assert_equal_tab(env, &test_number, "test=test", NULL);
	ft_clean_matrix((void **)cmd);

	ft_clean_matrix((void **)env);
}
