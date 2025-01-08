/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:17:09 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/08 18:23:35 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

static t_tree	*add_new_token(t_tree *tree, t_token token)
{
	t_tree	*tmp;

	tmp = tree_add_parent(tree, token);
	if (tmp)
		return (tmp);
	token_clear(token);
	tree_clear(&tree);
	ft_putendl_error("error malloc");
	return (NULL);
}

t_tree	*state_redir(t_tree *tree, t_queue *queue, t_token token)
{
	tree = add_new_token(tree, token);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	if (queue_first_name(queue) == TOKEN_CMD || queue_first_name(queue) == TOKEN_CMD)
	{
		token = queue_pop(queue);
		if (token.name == TOKEN_CMD)
			return (state_cmd(tree, queue, token));
		return (state_pipe(tree, queue, token));
	}
	// manage par error
	return (tree);
}

t_tree	*state_cmd(t_tree *tree, t_queue *queue, t_token token)
{
	tree = add_new_token(tree, token);
	if (tree == NULL || queue_is_empty(queue))
		return (tree);
	if (queue_first_name(queue) == TOKEN_PIPE)
	{
		token = queue_pop(queue);
		return (state_pipe(tree, queue, token));
	}
	// manage par error
	return (tree);
}

t_tree	*state_pipe(t_tree *tree, t_queue *queue, t_token token)
{
	t_tree	*sub_tree;
	int		result;

	tree = add_new_token(tree, token);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		// print error
		tree_clear(&tree);
		return (NULL);
	}
	token = queue_pop(queue);
	sub_tree = NULL;
	if (token.name == TOKEN_REDIR)
		sub_tree = state_redir(NULL, queue, token);
	else if (token.name == TOKEN_CMD)
		sub_tree = state_cmd(NULL, queue, token);
	// manage par
	if (sub_tree != NULL)
	{
		result = tree_push_right(tree, sub_tree);
		if (result == 0)
		{
			tree_clear(&sub_tree);
			tree_clear(&tree);
			return (NULL);
		}
		return (tree);
	}
	// manage par
	// print error
	tree_clear(&tree);
	return (NULL);
}

t_tree	*state_ope(t_tree *tree, t_queue *queue, t_token token)
{
	t_tree	*sub_tree;
	int		result;

	if (!tree)
	{
		// print error
		token_clear(token);
		return (NULL);
	}
	tree = add_new_token(tree, token);
	if (!tree)
		return (NULL);
	if (queue_is_empty(queue))
	{
		// print error
		tree_clear(&tree);
		return (NULL);
	}
	token = queue_pop(queue);
	sub_tree = NULL;
	if (token.name == TOKEN_REDIR)
		sub_tree = state_redir(NULL, queue, token);
	else if (token.name == TOKEN_CMD)
		sub_tree = state_cmd(NULL, queue, token);
	// manage par
	if (sub_tree != NULL)
	{
		result = tree_push_right(tree, sub_tree);
		if (result == 0)
		{
			tree_clear(&sub_tree);
			tree_clear(&tree);
			return (NULL);
		}
		return (tree);
	}
	// manage par
	// print error
	tree_clear(&tree);
	return (NULL);
}

//t_tree	*state_par(t_tree *tree, t_queue queue, t_token token) {}

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

static t_tree	*next_state(t_tree *tree, t_queue *queue, t_token token)
{
	if (token.name == TOKEN_REDIR)
		tree = state_redir(tree, queue, token);
	else if (token.name == TOKEN_CMD)
		tree = state_cmd(tree, queue, token);
	/*else if (token.name == TOKEN_PIPE)
		tree = state_pipe(tree, queue);*/
	else if (token.name == TOKEN_OPE)
		tree = state_ope(tree, queue, token);
	/*else if (token.name == TOKEN_PAR)
		tree = state_redir(tree, queue);*/
	else
	{
		// print error
		token_clear(token);
		tree_clear(&tree);
		return (NULL);
	}
	return (tree);
}

t_tree *get_tree(t_queue *queue)
{
	t_tree	*tree;
	t_token	token;

	tree = NULL;
	while (!queue_is_empty(queue))
	{
		token = queue_pop(queue);
		tree = next_state(tree, queue, token);
		if (tree == NULL)
			break;
	}
	queue_clear(queue);
	/*--//
	breadth_first_search(tree);
	ft_printf("\n\n");
	tree_traversal_in_order(tree);
	//--*/
	return (tree);
}
