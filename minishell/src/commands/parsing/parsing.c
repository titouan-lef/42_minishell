/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:49:43 by lguerbig          #+#    #+#             */
/*   Updated: 2025/01/07 18:51:41 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "commands.h"

/*
* Goal: Check if a there is an syntax error with parenthesis.
*
* Return: 0 if error, 1 if not.
*
* Warning: nb_par must not be null.
*/
int	valid_parenthesis(char *input)
{
	int		nb_par;

	nb_par = 0;
	while (*input)
	{
		if (*input == '(')
			nb_par++;
		if (*input == ')')
			nb_par--;
		if (nb_par < 0)
		{
			printf("syntax error near token '%c'\n", *input);
			return (0);
		}
		input++;
	}
	if (nb_par > 0)
	{
		printf("syntax error\n"); //heredoc ?
		return (0);
	}
	return (1);
}

static void manage_error(t_tree *tree, char *message_error)
{
	tree_clear(&tree);
	ft_putendl_error(message_error);
}

static t_tree	*tree_build(t_tree *tree, t_queue *queue)
{
	t_tree	*aux;
	t_token	token;
	int		result;

	if (queue_is_empty(queue))
	{
		if (tree_is_empty(tree))
			ft_putendl_error("todo");// change message
		return (tree);
	}
	token = queue_pop(queue);
	if (token.name == TOKEN_PAR)
	{
		result = (token.value[0][0] == '(');
		token_clear(token);
		if (result)
		{
			aux = tree_build(NULL, queue);
			if (!aux)
			{
				tree_clear(&tree);
				return (NULL);
			}
			if (tree_is_empty(tree))
				tree = aux;
			else
			{
				result = tree_push_right(tree, aux);
				if (result == 0)
				{
					tree_clear(&aux);
					tree_clear(&tree);
					return (NULL);
				}
			}
		}
		else
		{
			if (tree_is_empty(tree))
				ft_putendl_error("todo");// change message
			return (tree);
		}
	}
	else if (tree_is_empty(tree))
	{
		if (token.name == TOKEN_PIPE || token.name == TOKEN_OPE)
		{
			token_clear(token);
			manage_error(tree, "todo");// change message
			return (NULL);
		}
		tree = tree_create(token);
		if (!tree)
		{
			token_clear(token);
			manage_error(tree, "error malloc");// change message
			return (NULL);
		}
	}
	else if (token.name == TOKEN_PIPE || token.name == TOKEN_OPE)
	{
		if (queue_is_empty(queue))
		{
			token_clear(token);
			manage_error(tree, "todo");// change message
			return (NULL);
		}
		aux = tree_add_parent(tree, token);
		if (!aux)
		{
			token_clear(token);
			manage_error(tree, "error malloc");// change message
			return (NULL);
		}
		tree = aux;
		aux = tree_build(NULL, queue);
		if (!aux)
		{
			tree_clear(&tree);
			return (NULL);
		}
		result = tree_push_right(tree, aux);
		if (result == 0)
		{
			tree_clear(&aux);
			tree_clear(&tree);
			return (NULL);
		}
	}
	else
	{
		aux = tree_add_parent(tree, token);
		if (!aux)
		{
			token_clear(token);
			manage_error(tree, "error malloc");// change message
			return (NULL);
		}
		tree = aux;
	}
	return (tree_build(tree, queue));
}

static void	tree_traversal_in_order(t_tree *tree)
{
	if (tree != NULL)
	{
		tree_traversal_in_order(tree->left);
		ft_printf("node : %d, value : %s\n", tree->token.name, tree->token.value[0]);
		tree_traversal_in_order(tree->right);
	}
}

static void	breadth_first_search(t_tree *tree)
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

	/*element = (t_element_test *)malloc(sizeof(t_element_test));
	element->tree = node;
	element->next = NULL;
	if (queue.head == NULL)
		queue.head = element;
	else
		queue.tail->next = element;
	queue.tail = element;


	element = queue.head;
	queue.head = element->next;
	node = element->tree;
	free(element);
	if (queue.head == NULL)
		queue.tail = NULL;*/

	// create
	queue.head = NULL;
	queue.tail = NULL;
	/**/
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
	/**/
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
		/**/
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
			/**/
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
			/**/
		}
	}
}

t_tree	*get_tree(t_queue *queue)
{
	t_tree	*tree;

	if (queue_is_empty(queue))
		return (NULL);
	tree = tree_build(NULL, queue);
	queue_clear(queue);
	breadth_first_search(tree);
	ft_printf("\n\n");
	tree_traversal_in_order(tree);
	return (tree);
}
