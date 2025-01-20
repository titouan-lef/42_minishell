/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:16:01 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/20 16:10:16 by lguerbig         ###   ########.fr       */
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

	start_test("redirections");
	test_number = 1;
	
	/*--- test 1 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">out", NULL));
	make_redirs(token, NULL);
	assert_redir_out(out, &test_number, "out", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 2 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">out", ">outfile", NULL));
	make_redirs(token, NULL);
	assert_redir_out(out, &test_number, "out", "outfile", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 3 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">>out", ">outfile", NULL));
	make_redirs(token, NULL);
	assert_redir_out(out, &test_number, "out", "outfile", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 4 ---*/
	out.save_out = dup(STDOUT_FILENO);
	out.save_err = dup(STDERR_FILENO);
	token = token_create(TOKEN_REDIR, built_tab(">>out", ">outfile", NULL));
	close(open("out", O_CREAT, 0644));
	make_redirs(token, NULL);
	assert_redir_out(out, &test_number, "out", "outfile", NULL);
	token_clear(token);
	fflush(stdout);

	/*--- test 5 ---*/
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab(">>out", ">outfile", NULL));
	open("out", O_CREAT, 000);
	make_redirs(token, NULL);
	set_normal_outputs(&out);
	assert_equal_err("minishell: out: Permission denied", &test_number);
	unlink("out");
	token_clear(token);
	fflush(stdout);

	/*--- test 6 ---*/
	redirect_outputs(&out);
	token = token_create(TOKEN_REDIR, built_tab(">out", ">outfile", NULL));
	open("out", O_CREAT, 000);
	make_redirs(token, NULL);
	set_normal_outputs(&out);
	assert_equal_err("minishell: out: Permission denied", &test_number);
	unlink("out");
	token_clear(token);
	fflush(stdout);

	/*--- test 7 ---*/
	redirect_outputs(&out);
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", NULL));
	make_redirs(token, NULL);
	set_normal_outputs(&out);
	assert_equal_err("minishell: in: No such file or directory", &test_number);
	set_normal_input(&in);
	token_clear(token);

	/*--- test 8 ---*/
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", NULL));
	close(open("in", O_CREAT, 0644));
	make_redirs(token, NULL);
	assert_redir_in("in", "test\n", 0, &test_number);
	set_normal_input(&in);
	token_clear(token);

	/*--- test 9 & 10 ---*/
	in.save_in = dup(STDIN_FILENO);
	token = token_create(TOKEN_REDIR, built_tab("<in", "<infile", NULL));
	close(open("in", O_CREAT, 0644));
	close(open("infile", O_CREAT, 0644));
	make_redirs(token, NULL);
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
	make_redirs(token, NULL);
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
	make_redirs(token, here_docs);
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
	make_redirs(token, here_docs);
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
	make_redirs(token, here_docs);
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
	make_redirs(token, here_docs);
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
	make_redirs(token, here_docs);
	token_clear(token);
	assert_redir_in(((t_here_doc *)here_docs->content)->filename, "$USER\n", 1, &test_number);
	clear_here_docs(here_docs);
	unlink("here_doc");
	set_normal_input(&in);
}
