/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/28 21:43:27 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

void	test_cd(char **envp)
{
	size_t	test_number;
	char	**env = strdup_tab(envp);
	char	**env_tmp;
	char	**cmd;
	char	*pwd;
	char	*save_pwd;
	char	*home;
	char	*tmp;

	start_test("cd");
	test_number = 1;

	save_pwd = get_cwd(env);

	/*--- test 1 ---*/
	cmd = built_tab("cd", "unit_test", NULL);
	pwd = get_cwd(env);
	cd(cmd, env);
	ft_clean_matrix((void **)cmd);
	tmp = ft_strjoin(pwd, "/unit_test");
	free(pwd);
	pwd = get_cwd(env);
	assert_equal_s(tmp, pwd, &test_number);
	free(tmp);
	free(pwd);

	/*--- test 2 ---*/
	cmd = built_tab("cd", "..", NULL);
	cd(cmd, env);
	ft_clean_matrix((void **)cmd);
	pwd = get_cwd(env);
	assert_equal_s(save_pwd, pwd, &test_number);
	free(pwd);

	free(save_pwd);
	save_pwd = get_cwd(env);

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
	pwd = get_cwd(env);
	assert_equal_s(home, pwd, &test_number);
	free(pwd);

	/*--- test 4 ---*/
	tmp = ft_strjoin("OLDPWD=", save_pwd);
	env_tmp = built_tab(tmp, NULL);
	free(tmp);
	cmd = built_tab("cd", "-", NULL);
	int save = dup(STDOUT_FILENO);
	int fd = open("/dev/null", O_WRONLY);
	fflush(stdout);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cd(cmd, env_tmp);
	dup2(save, STDOUT_FILENO);
	close(save);
	ft_clean_matrix((void **)cmd);
	pwd = get_cwd(env);
	ft_clean_matrix((void **)env_tmp);
	assert_equal_s(save_pwd, pwd, &test_number);
	chdir(save_pwd);
	free(pwd);

	free(save_pwd);
	free(home);
	ft_clean_matrix((void **)env);
}
