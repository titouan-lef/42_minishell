/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:53:05 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/14 20:32:59 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static int	redir_execution(t_token token, int is_piped)
{
	int	result;

	result = make_redirs(token);
	if (is_piped)
		exit(result);
	return (result);
}

static int	cmd_execution(t_tree *tree, t_token token, int is_piped)
{
	int	result;

	if (tree->left != NULL)
	{
		result = tree_execution(tree->left, 0);
		if (result != 0)
		{
			if (is_piped)
				exit(result);
			return (result);
		}
	}
	result = make_cmd(token, is_piped);//todo revoir
	if (is_piped)
		exit(result);
	return (result);
}

static int	sub_pipe_execution(t_tree *tree, t_stack *stack)// free l'arbre enfant
{
	int	pid;
	int	result;

	if (tree->left->token.name == TOKEN_PIPE)
	{
		result = sub_pipe_execution(tree->left, stack);
		if (result)
			return (result);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putendl_error("fork failed");
			return (1);
		}
		else if (pid == 0)
			tree_execution(tree->left, 1);
		else
			stack->push(pid);
	}
	if (tree->right->token.name == TOKEN_PIPE)
	{
		result = sub_pipe_execution(tree->right, stack);
		if (result)
			return (result);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putendl_error("fork failed");
			return (1);
		}
		else if (pid == 0)
			tree_execution(tree->right, 1);
		else
			stack->push(pid);
	}
	return (0);
}

static int	pipe_execution(t_tree *tree)
{
	int	result;
	t_stack	*stack;
	int	pid;
	int	last_pid;
	int	status;

	//statck = stack_create();
	result = sub_pipe_execution(tree, stack);
	if (result)
	{
		stack_free(stack);
		return (result);
	}
	last_pid = stack->first.pid;
	while (!stack_is_empty(stack))
	{
		stack_pop(stack);
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
			result = status;
	}
	return (result);

	/*if (tree->left->token.name != TOKEN_PIPE)
	{
		//fork
		result = tree_execution(tree->left, 1);
		//exit(result);
	}
	else
		result = tree_execution(tree->left, 0);
	if (tree->right->token.name != TOKEN_PIPE)
	{
		//fork
		result = tree_execution(tree->right, 1);
		//exit(result);
	}
	else
		result = tree_execution(tree->right, 0);
	// if (fork1 et fork2)
	//		waitpid(pid, &status, 0);
	//		waitpid(pid, &status, 0);
	// if (fork1 ou fork2)
	// 		waitpid(pid, &status, 0);
	return (result);*/
}

static int	ope_execution(t_tree *tree, t_token token, int is_piped)
{
	int	result;

	result = tree_execution(tree->left, 0);
	if (ft_strcmp(token.value[0], "&&") == 0)
	{
		if (result != 0)
		{
			if (is_piped)
				exit(result);
			return (result);
		}
		result = tree_execution(tree->right, 0);
	}
	else
	{
		if (result == 0)
		{
			if (is_piped)
				exit(result);
			return (result);
		}
		result = tree_execution(tree->right, 0);
	}
	if (is_piped)
		exit(result);
	return (result);
}

static int	tree_execution(t_tree *tree, int is_piped)
{
	t_token	token;
	int		result;

	token = tree->token;
	if (token.name == TOKEN_REDIR)
		result = redir_execution(token, is_piped);
	if (token.name == TOKEN_CMD)
		result = cmd_execution(tree, token, is_piped);
	if (token.name == TOKEN_PIPE)
		result = pipe_execution(tree);
	else
		result = ope_execution(tree, token, is_piped);
	return (result);
}

int make_execution(t_tree *tree)
{
	int	result;

	result = tree_execution(tree, 0);
	return (result);
}