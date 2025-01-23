/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:17:09 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/23 18:16:52 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/*
* Goal: Print errors syntaxes define by the redirections.
*
* Warning: If a redir start by a digit, print the number.
* Else print <, >, << or >>.
*/
static void	print_error_redir(char *token_error)
{
	size_t	i;

	if (ft_isdigit(token_error[0]))
	{
		i = 1;
		while (ft_isdigit(token_error[i]))
			++i;
		token_error[i] = '\0';
		print_error_token_value(token_error);
		return ;
	}
	if (token_error[0] == token_error[1])
		token_error[2] = '\0';
	else
		token_error[1] = '\0';
	print_error_token_value(token_error);
}

/*
* Goal: Add each here_dc found in the list and print errors syntaxes in
* redirections.
*
* Return: 0 if succed, 1 else.
*
* Warning: If a syntax error is detected, it's the next redir which is printed
* or the next token if it was the last redir.
*/
static int	update_here_docs(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	int		result;
	char	*token_error;

	result = detect_here_docs(tree->token, here_docs);
	if (result == -1)
		return (0);
	if (result == -2)
		return (1);
	token_error = tree->token.value[result + 1];
	if (!token_error)
		print_error_token(queue);
	else
		print_error_redir(token_error);
	return (1);
}

/*
* Goal: Add and manage redirection in tree.
*
* Return: The new tree (or NULL if error).
*/
t_tree	*state_redir(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree_is_empty(tree))
		return (NULL);
	if (update_here_docs(tree, queue, here_docs))
	{
		tree_clear(&tree);
		return (NULL);
	}
	if (queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_CMD)
		tree = state_cmd(tree, queue, here_docs);
	else if (next_token_name == TOKEN_PIPE)
		tree = state_junction_ope(tree, queue, here_docs);
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

/*
* Goal: Add and manage command in tree.
*
* Return: The new tree (or NULL if error).
*/
t_tree	*state_cmd(t_tree *tree, t_queue *queue, t_list **here_docs)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree_is_empty(tree) || queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_PIPE)
		tree = state_junction_ope(tree, queue, here_docs);
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		if (tree->token.value[1] == NULL)// && tree->left == NULL --> redir
			remove_token(queue);
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}
