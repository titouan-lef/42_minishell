/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/27 16:39:15 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

void	test_cd(char **envp)
{
	size_t	test_number;
	char	**env = strdup_tab(envp);
	char	**cmd;
	char	*pwd;
	char	*save_pwd;
	char	*home;
	char	*tmp;

	start_test("cd");
	test_number = 1;

	save_pwd = get_cdw(env);

	/*--- test 1 ---*/
	cmd = built_tab("cd", "unit_test", NULL);
	pwd = get_cdw(env);
	cd(cmd, env);
	ft_clean_matrix((void **)cmd);
	tmp = ft_strjoin(pwd, "/unit_test");
	free(pwd);
	pwd = get_cdw(env);
	assert_equal_s(pwd, tmp, &test_number);
	free(tmp);
	free(pwd);

	/*--- test 2 ---*/
	cmd = built_tab("cd", "..", NULL);
	cd(cmd, env);
	ft_clean_matrix((void **)cmd);
	pwd = get_cdw(env);
	assert_equal_s(pwd, save_pwd, &test_number);
	free(pwd);

	free(save_pwd);
	save_pwd = get_cdw(env);

	int i = 0;
	while (env[i])
		if (ft_strncmp("HOME=", env[i++], 5) == 0)
			break ;
	--i;
	home = ft_strdup(env[i] + 5);

	/*--- test 3 ---*/
	cmd = built_tab("cd", NULL);
	cd(cmd, env);
	ft_clean_matrix((void **)cmd);
	pwd = get_cdw(env);
	assert_equal_s(pwd, home, &test_number);
	free(pwd);

	/*--- test 4 ---*/
	cmd = built_tab("cd", "-", NULL);
	cd(cmd, env);
	ft_clean_matrix((void **)cmd);
	pwd = get_cdw(env);
	assert_equal_s(pwd, save_pwd, &test_number);
	free(pwd);

	free(save_pwd);


	free(home);
	ft_clean_matrix((void **)env);
}
