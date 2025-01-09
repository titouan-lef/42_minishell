/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:17:09 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/09 17:38:29 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

static t_tree	*add_new_token(t_tree *tree, t_queue *queue)
{
	t_tree	*tmp;
	t_token	token;

	token = queue_pop(queue);
	tmp = tree_add_parent(tree, token);
	if (tmp)
		return (tmp);
	token_clear(token);
	tree_clear(&tree);
	ft_putendl_error("error malloc");
	return (NULL);
}

static void	remove_token(t_queue *queue)
{
	t_token	token;

	token = queue_pop(queue);
	token_clear(token);
}

static void	print_error_token(t_queue *queue)
{
	t_token	token;

	token = queue_pop(queue);
	ft_putstr_error("bash: syntax error near unexpected token `");
	ft_putstr_error(token.value[0]);
	ft_putendl_error("'");
	token_clear(token);
}

/*static t_tree	*next_commun_state(t_tree *tree, t_queue *queue, t_token_name token_name)
{
	if (token_name == TOKEN_REDIR)
		tree = state_redir(tree, queue);
	else if (token_name == TOKEN_CMD)
		tree = state_cmd(tree, queue);
	else if (token_name == TOKEN_PAR_OPEN)
		tree = state_par_open(tree, queue);
	else
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}*/

t_tree	*state_redir(t_tree *tree, t_queue *queue)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_CMD || next_token_name == TOKEN_PIPE)
	{
		if (next_token_name == TOKEN_CMD)
			return (state_cmd(tree, queue));
		return (state_pipe(tree, queue));
	} else if (next_token_name == TOKEN_PAR_OPEN)
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_cmd(t_tree *tree, t_queue *queue)
{
	t_token_name	next_token_name;

	tree = add_new_token(tree, queue);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	next_token_name = queue_first_name(queue);
	if (next_token_name == TOKEN_PIPE)
		return (state_pipe(tree, queue));
	else if (next_token_name == TOKEN_PAR_OPEN)
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_pipe(t_tree *tree, t_queue *queue)//
{
	t_token_name	token_name;
	t_tree			*sub_tree;
	int				result;

	tree = add_new_token(tree, queue);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		ft_putendl_error("to define");
		//print_error_token("|");// no heardoc ?
		tree_clear(&tree);
		return (NULL);
	}
	token_name = queue_first_name(queue);
	if (token_name == TOKEN_REDIR)
		sub_tree = state_redir(NULL, queue);
	else if (token_name == TOKEN_CMD)
		sub_tree = state_cmd(NULL, queue);
	else if (token_name == TOKEN_PAR_OPEN)
		sub_tree = state_par_open(NULL, queue);
	else
	{
		sub_tree = NULL;
		print_error_token(queue);
	}
	if (!sub_tree)
	{
		tree_clear(&tree);
		return (NULL);
	}
	result = tree_push_right(tree, sub_tree);
	if (result == 0)
	{
		tree_clear(&sub_tree);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_ope(t_tree *tree, t_queue *queue)//
{
	t_token_name	token_name;
	t_tree			*sub_tree;
	int				result;

	if (!tree)
	{
		print_error_token(queue);
		return (NULL);
	}
	tree = add_new_token(tree, queue);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		ft_putendl_error("to define");
		//print_error_token("&&");// no heardoc ?
		tree_clear(&tree);
		return (NULL);
	}
	token_name = queue_first_name(queue);
	if (token_name == TOKEN_REDIR)
		sub_tree = state_redir(NULL, queue);
	else if (token_name == TOKEN_CMD)
		sub_tree = state_cmd(NULL, queue);
	else if (token_name == TOKEN_PAR_OPEN)
		sub_tree = state_par_open(NULL, queue);
	else
	{
		sub_tree = NULL;
		print_error_token(queue);
	}
	if (!sub_tree)
	{
		tree_clear(&tree);
		return (NULL);
	}
	result = tree_push_right(tree, sub_tree);
	if (result == 0)
	{
		tree_clear(&sub_tree);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

/*t_tree	*state_par_close(t_tree *tree, t_queue *queue, t_token token) {}*/

/*static void	tree_traversal_in_order(t_tree *tree)
{
	if (tree != NULL)
	{
		tree_traversal_in_order(tree->left);
		ft_printf("node : %d, value : %s\n", tree->token.name, tree->token.value[0]);
		tree_traversal_in_order(tree->right);
	}
}*/

/*static void	breadth_first_search(t_tree *tree)
{
	typedef struct s_element_test
	{
		t_tree 					*tree;
		int						depth;
		struct s_element_test	*next;
	}	t_element_test;

	typedef struct s_queue_test
	{
		t_element_test	*head;
		t_element_test	*tail;
	}	t_queue_test;

	t_queue_test	queue;
	t_element_test	*element;
	t_tree			*node;
	int				i = -1;
	int				depth;

	// create
	queue.head = NULL;
	queue.tail = NULL;
	//--//
	// push
	element = (t_element_test *)malloc(sizeof(t_element_test));
	element->tree = tree;
	element->depth = 0;
	element->next = NULL;
	if (queue.head == NULL)
		queue.head = element;
	else
		queue.tail->next = element;
	queue.tail = element;
	//--//
	while (queue.head != NULL)
	{
		// pop
		element = queue.head;
		queue.head = element->next;
		depth = element->depth;
		node = element->tree;
		free(element);
		if (queue.head == NULL)
			queue.tail = NULL;
		//--//
		if (depth != i)
		{
			++i;
			ft_printf("\nDepth : %d\n",i);
		}
		ft_printf("  - node : %s\n", node->token.value[0]);
		if (node->left != NULL)
		{
			// push
			element = (t_element_test *)malloc(sizeof(t_element_test));
			element->tree = node->left;
			element->depth = i + 1;
			element->next = NULL;
			if (queue.head == NULL)
				queue.head = element;
			else
				queue.tail->next = element;
			queue.tail = element;
			//--//
		}
		if (node->right != NULL)
		{
			// push
			element = (t_element_test *)malloc(sizeof(t_element_test));
			element->tree = node->right;
			element->depth = i + 1;
			element->next = NULL;
			if (queue.head == NULL)
				queue.head = element;
			else
				queue.tail->next = element;
			queue.tail = element;
			//--//
		}
	}
}*/

static t_tree	*next_state(t_tree *tree, t_queue *queue)
{
	t_token_name	token_name;

	token_name = queue_first_name(queue);
	if (token_name == TOKEN_REDIR)
		tree = state_redir(tree, queue);
	else if (token_name == TOKEN_CMD)
		tree = state_cmd(tree, queue);
	else if (token_name == TOKEN_OPE)
		tree = state_ope(tree, queue);
	else if (token_name == TOKEN_PAR_OPEN)
		tree = state_par_open(tree, queue);
	else
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree	*state_par_open(t_tree *tree, t_queue *queue)
{
	t_token_name	token_name;

	if (!tree_is_empty(tree) || queue_is_empty(queue))
	{
		print_error_token(queue);
		tree_clear(&tree);
		return (NULL);
	}
	remove_token(queue);
	token_name = queue_first_name(queue);
	while (token_name != TOKEN_PAR_CLOSE)
	{
		tree = next_state(tree, queue);
		if (tree == NULL)
			return (NULL);
		token_name = queue_first_name(queue);
	}
	if (tree_is_empty(tree))
	{
		print_error_token(queue);
		return (NULL);
	}
	remove_token(queue);
	return (tree);
}

t_tree *get_tree(t_queue *queue)
{
	t_tree	*tree;

	tree = NULL;
	while (!queue_is_empty(queue))
	{
		tree = next_state(tree, queue);
		if (tree == NULL)
			break;
	}
	queue_clear(queue);
	tree_clear(&tree);//todo remove
	tree = NULL;//todo remove
	/*--//
	breadth_first_search(tree);
	ft_printf("\n\n");
	tree_traversal_in_order(tree);
	//--*/
	return (tree);
}
