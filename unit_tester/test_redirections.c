/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/23 17:14:14 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static void	assert_redir_out(t_out out, size_t *i, ...)
{
	char	*expected;
	char	*result;
	char	*file;
	va_list	args;
	va_list	args_cpy;
	int		nb_args;
	int		fd;

	out.out = STDOUT_FILENO;
	out.err = STDERR_FILENO;
	va_start(args, i);
	nb_args = 0;
	va_copy(args_cpy, args);
	while(va_arg(args_cpy, char *))
		++nb_args;
	va_end(args_cpy);
	if (out.out == out.save_out)
	{
		set_normal_outputs(&out);
		print_ko("", "(not redirected)", i);
		return ;
	}
	if (write(STDOUT_FILENO, "test\n", 5) == -1)
	{
		set_normal_outputs(&out);
		print_ko("", "(persission denied)", i);
		return ;
	}
	expected = "";
	while (nb_args > 0)
	{
		file = (char *)va_arg(args, char *);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			set_normal_outputs(&out);
			print_ko(file, "(file does not exist)", i);
			unlink(file);
			return ;
		}
		result = calloc(10000,sizeof(char)); //rip protection
		if (read(fd, result, 10000) == -1)
		{
			set_normal_outputs(&out);
			print_ko(file, "(permission denied)", i);
			free(result);
			close(fd);
			unlink(file);
			return ;
		}
		close(fd);
		unlink(file);
		if (nb_args == 1)
			expected = "test\n";
		if (strcmp(expected, result))
		{
			set_normal_outputs(&out);
			print_ok(i);
			free(result);
			return ;
		}
		free(result);
		nb_args--;
	}
	set_normal_outputs(&out);
	print_ok(i);
}

static void	assert_redir_in(char *file, char *expected, int here_doc, size_t *i)
{
	char	*result;
	int		fd;

	if (!here_doc)
	{
		fd = open(file, O_WRONLY);
		if (fd == -1)
		{
			print_ko(file, "(file does not exist)", i);
			return ;
		}
		if (write(fd, "test\n", 5) == -1)
		{
			print_ko(file, "(permission denied)", i);
			return ;
		}
		close(fd);
	}
	result = calloc(10000,sizeof(char)); //rip protection
	if (read(STDIN_FILENO, result, 10000) == -1)
	{
		print_ko(file, "(permission denied)", i);
		return ;
	}
	unlink(file);
	if (strcmp(expected, result) == 0)
		print_ok(i);
	else
		print_ko(expected, result, i);
	free(result);
}

void	test_redirs(char **env)
{
	t_list	*here_docs;
	size_t	test_number;
	t_token	token;
	t_out	out;
	t_in	in;
	int		fd;
	int		result;

	start_test("redirections");
	test_number = 1;

	/*--- test 1 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">out", NULL));
	redir_manager(token, NULL);
	assert_redir_out(out, &test_number, "out", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 2 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">out", ">outfile", NULL));
	redir_manager(token, NULL);
	assert_redir_out(out, &test_number, "out", "outfile", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 3 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">>out", ">outfile", NULL));
	redir_manager(token, NULL);
	assert_redir_out(out, &test_number, "out", "outfile", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 4 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">>out", ">outfile", NULL));
	close(open("out", O_CREAT, 0644));
	redir_manager(token, NULL);
	assert_redir_out(out, &test_number, "out", "outfile", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 5 ---*/
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab(">>out", ">outfile", NULL));
	open("out", O_CREAT, 000);
	redir_manager(token, NULL);
	set_normal_outputs(&out);
	assert_equal_err("minishell: out: Permission denied", &test_number);
	unlink("out");
	token_clear(token);
	fflush(stdout);

	/*--- test 6 ---*/
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab(">out", ">outfile", NULL));
	open("out", O_CREAT, 000);
	redir_manager(token, NULL);
	set_normal_outputs(&out);
	assert_equal_err("minishell: out: Permission denied", &test_number);
	unlink("out");
	token_clear(token);
	fflush(stdout);

	/*--- test 7 ---*/
	redirect_outputs(&out);
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", NULL));
	redir_manager(token, NULL);
	set_normal_outputs(&out);
	assert_equal_err("minishell: in: No such file or directory", &test_number);
	set_normal_input(&in);
	token_clear(token);

	/*--- test 8 ---*/
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", NULL));
	close(open("in", O_CREAT, 0644));
	redir_manager(token, NULL);
	assert_redir_in("in", "test\n", 0, &test_number);
	set_normal_input(&in);
	token_clear(token);

	/*--- test 9 & 10 ---*/
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", "<infile", NULL));
	close(open("in", O_CREAT, 0644));
	close(open("infile", O_CREAT, 0644));
	redir_manager(token, NULL);
	assert_redir_in("in", "", 0, &test_number);
	assert_redir_in("infile", "test\n", 0, &test_number);
	set_normal_input(&in);
	token_clear(token);

	/*--- test 11 & 12 & 13 ---*/
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", "<infile", "<testin", NULL));
	close(open("in", O_CREAT, 0644));
	close(open("infile", O_CREAT, 0644));
	close(open("testin", O_CREAT, 0644));
	redir_manager(token, NULL);
	assert_redir_in("in", "", 0, &test_number);
	assert_redir_in("infile", "", 0, &test_number);
	assert_redir_in("testin", "test\n", 0, &test_number);
	set_normal_input(&in);
	token_clear(token);

	fflush(stdout);

	/*--- test 14 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 15);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
	redir_manager(token, here_docs);
	token_clear(token);
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, "test\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 15 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "$USER\nhere_doc\n", 16);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
	redir_manager(token, here_docs);
	token_clear(token);
	char *expected = ft_strjoin(getenv("USER"),"\n");
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, expected, 1, &test_number);
	free(expected);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 16 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<\"here_doc\"", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "$USER\nhere_doc\n", 18);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
	redir_manager(token, here_docs);
	token_clear(token);
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, "$USER\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 17 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<\'\"\'here_doc", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "$USER\n\"here_doc\n", 18);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
	redir_manager(token, here_docs);
	token_clear(token);
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, "$USER\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 18 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_\'doc\'", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "$USER\nhere_doc\n", 18);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
	redir_manager(token, here_docs);
	token_clear(token);
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, "$USER\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 19 && 20 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">ok", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 15);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	redir_manager(token, here_docs);
	assert_redir_out(out, &test_number, "ok", NULL);
	//set_normal_outputs(&out);
	token_clear(token);
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, "test\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	unlink("ok");
	set_normal_input(&in);

	/*--- test 21 && 22 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", "<<ok", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\ntest2\nok\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	redir_manager(token, here_docs);
	set_normal_outputs(&out);
		if (result == -1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	assert_redir_in("ok", "test2\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 23 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">", "<<ok", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 24 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">>", "<<ok", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 25 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", "<", "<<ok", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 26 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", "<<", "<<ok", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 27 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 28 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">>", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 29 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", "<", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 30 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", "<<", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 1)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 31 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">out", ">", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 2)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 32 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">out", ">>", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 2)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 33 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">out", "<", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 2)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);

	/*--- test 34 ---*/
	in.save_in = dup(STDIN_FILENO);
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab("<<here_doc", ">out", "<<", NULL));
	fd = open("here_doc", O_WRONLY | O_CREAT, 0644);
	write(fd, "test\nhere_doc\n", 23);
	close(fd);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	here_docs = NULL;
	result = detect_here_docs(token, &here_docs);
	read_here_docs(here_docs, env);
	set_normal_outputs(&out);
		if (result == 2)
		print_ok(&test_number);
	else
		print_ko("", "error detected in redir", &test_number);
	token_clear(token);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);
}
