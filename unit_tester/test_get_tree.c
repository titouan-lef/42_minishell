/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:12:14 by tle-floc          #+#    #+#             */
/*   Updated: 2025/02/06 19:32:41 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

typedef struct s_node
{
	t_tree 			*tree;
	int				depth;
	struct s_node	*next;
}	t_node;

typedef struct s_queue_node4
{
	t_node	*head;
	t_node	*tail;
}	t_queue_node;

static int	queue_node_is_empty(t_queue_node *queue)
{
	return (queue->head == NULL);
}

static void	queue_node_clear(t_queue_node *queue)
{
	t_node	*node;

	while (!queue_node_is_empty(queue))
	{
		node = queue->head;
		queue->head = node->next;
		tree_clear(&node->tree);
		free(node);
		node = NULL;
	}
	queue->tail = NULL;
}

static int	queue_node_push(t_queue_node *queue, t_tree *tree, int depth)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		queue_node_clear(queue);
		ft_putendl_error("Error malloc queue push");
		return (0);
	}
	node->tree = tree;
	node->depth = depth;
	node->next = NULL;
	if (queue_node_is_empty(queue))
		queue->head = node;
	else
		queue->tail->next = node;
	queue->tail = node;
	return (1);
}

static t_tree	*queue_node_pop(t_queue_node *queue)
{
	t_node	*node;
	t_tree	*tree;

	node = queue->head;
	queue->head = node->next;
	tree = node->tree;
	free(node);
	if (queue->head == NULL)
		queue->tail = NULL;
	return (tree);
}

static t_queue_node	queue_node_create(void)
{
	t_queue_node	queue;

	queue.head = NULL;
	queue.tail = NULL;
	return (queue);
}

/*static void	breadth_first_search(t_tree *tree)
{
	t_queue_node	queue;
	t_tree 			*aux;
	int				i = -1;
	int				depth;

	if (!tree)
		return ;
	queue = queue_node_create();
	queue_node_push(&queue, tree, 0);
	while (!queue_node_is_empty(&queue))
	{
		depth = queue.head->depth;
		aux = queue_node_pop(&queue);
		if (depth != i)
		{
			++i;
			ft_printf("Depth : %d\n",i);
		}
		ft_printf("  - node : %s\n", aux->token.value[0]);
		if (aux->left != NULL)
			queue_node_push(&queue, aux->left, i + 1);
		else
			ft_printf("    - end left\n");
		if (aux->right != NULL)
			queue_node_push(&queue, aux->right, i + 1);
		else
			ft_printf("    - end right\n");
		ft_printf("\n");
	}
}*/

static void	breadth_first_search(t_tree *tree)
{
	t_queue_node	queue;
	t_tree 			*aux;
	int				i = -1;
	int				depth;

	if (!tree)
		return ;
	queue = queue_node_create();
	queue_node_push(&queue, tree, 0);
	while (!queue_node_is_empty(&queue))
	{
		depth = queue.head->depth;
		aux = queue_node_pop(&queue);
		if (depth != i)
		{
			++i;
			ft_printf("%d\n",i);
		}
		if (aux->token.redir != NULL && aux->token.redir[0])
		{
			ft_printf("%s", aux->token.redir[0]);
			for (int j = 1; aux->token.redir[j] != NULL; ++j)
				ft_printf(" %s", aux->token.redir[j]);
			if (aux->token.value != NULL)
				ft_printf("\n");
		}
		if (aux->token.value != NULL)
			ft_printf("%s", aux->token.value[0]);
		if (aux->left != NULL)
			queue_node_push(&queue, aux->left, i + 1);
		else
			ft_printf(" l");
		if (aux->right != NULL)
			queue_node_push(&queue, aux->right, i + 1);
		else
			ft_printf(" r");
		ft_printf("\n");
	}
}

static char **create_token_value(char *value)
{
	char **result;

	result = calloc(2, sizeof(char *));
	result[0] = ft_strdup(value);
	return (result);
}

static char **create_token_value2(char *value, char *value2)
{
	char **result;

	result = calloc(3, sizeof(char *));
	result[0] = ft_strdup(value);
	result[1] = ft_strdup(value2);
	return (result);
}

static void write_result(t_queue *queue, t_data *data)
{
	t_out	outputs;

	redirect_outputs(&outputs);
	parser(queue, data);
	clear_here_docs(data->lst);
	breadth_first_search(data->tree);
	set_normal_outputs(&outputs);
	tree_clear(&data->tree);
}

// echo && cat
static void test_get_tree1(t_data *data)
{

	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));

	write_result(&queue, data);
}

// echo
static void test_get_tree2(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));

	write_result(&queue, data);
}

// echo &&
static void test_get_tree3(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));

	write_result(&queue, data);
}

// echo && cat | grep
static void test_get_tree4(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), NULL));

	write_result(&queue, data);
}

// <redir1 echo && cat | <redir2 grep || cut
static void test_get_tree5(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));

	write_result(&queue, data);
}

// <redir1 echo && cat | (<redir2 grep || cut)
static void test_get_tree6(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// <redir1 echo && cat | <redir2 grep || cut
static void test_get_tree7(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));

	write_result(&queue, data);
}

// <redir1 echo && cat | (<redir2 grep (|| cut))
static void test_get_tree8(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// <redir1 echo && cat | (<redir2 grep || (cut))
static void test_get_tree9(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// ()
static void test_get_tree10(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// (echo)
static void test_get_tree11(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// (echo ||)
static void test_get_tree12(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// (echo |)
static void test_get_tree13(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// (echo | cat)
static void test_get_tree14(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// (echo || cat)
static void test_get_tree15(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

//
static void test_get_tree16(t_data *data)
{
	t_queue	queue = queue_create();

	write_result(&queue, data);
}

// <redir1 && cat | (<redir2 grep || (<redir3))
static void test_get_tree17(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, NULL, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, NULL, create_token_value("<redir3")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// <redir1
static void test_get_tree18(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, NULL, create_token_value("<redir1")));

	write_result(&queue, data);
}

// <redir1 echo | cat | <redir2 grep | cut
static void test_get_tree19(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|1"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|2"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|3"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));

	write_result(&queue, data);
}

// echo |
static void test_get_tree20(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));

	write_result(&queue, data);
}

// echo | )
static void test_get_tree21(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo | (
static void test_get_tree22(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));

	write_result(&queue, data);
}

// echo | (cat && grep))
static void test_get_tree23(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo | )cat && grep()
static void test_get_tree24(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")1"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo | cat (grep)
static void test_get_tree25(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo (
static void test_get_tree26(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));

	write_result(&queue, data);
}

// &&
static void test_get_tree27(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));

	write_result(&queue, data);
}

// echo (( cat )
static void test_get_tree28(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// )
static void test_get_tree29(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// (
static void test_get_tree30(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));

	write_result(&queue, data);
}

//echo <
static void test_get_tree31(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<")));

	write_result(&queue, data);
}

//echo <<
static void test_get_tree32(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<<")));

	write_result(&queue, data);
}

//echo >
static void test_get_tree33(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value(">")));

	write_result(&queue, data);
}

//echo >>
static void test_get_tree34(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value(">>")));

	write_result(&queue, data);
}

//echo > &&
static void test_get_tree35(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value(">")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));

	write_result(&queue, data);
}

//echo > && echo coucou
static void test_get_tree36(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value(">")));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo", "coucou"), NULL));

	write_result(&queue, data);
}

//echo > >out
static void test_get_tree37(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value2(">", ">out")));

	write_result(&queue, data);
}

//echo > >>out
static void test_get_tree38(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value2(">", ">>out")));

	write_result(&queue, data);
}

// echo |1 (cat && grep) |2 sort || (cut |3 wc)
static void test_get_tree39(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|1"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|2"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("sort"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|3"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("wc"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo |1 cat |2 sort || (cut |3 wc)
static void test_get_tree40(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|1"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|2"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("sort"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|3"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("wc"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo |1 (cat) |2 sort || (cut |3 wc)
static void test_get_tree41(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|1"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|2"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("sort"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("||"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut"), NULL));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|3"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("wc"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));

	write_result(&queue, data);
}

// echo oui (
static void test_get_tree42(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo", "oui"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));

	write_result(&queue, data);
}

// echo redir (
static void test_get_tree43(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo"), create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));

	write_result(&queue, data);
}

// echo oui >
static void test_get_tree44(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo", "oui"), create_token_value(">")));

	write_result(&queue, data);
}

// echo oui >>
static void test_get_tree45(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo", "oui"), create_token_value(">>")));

	write_result(&queue, data);
}

// (echo1 oui && echo2 non) echo3 test
static void test_get_tree46(t_data *data)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("("), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo1", "oui"), NULL));
	queue_push(&queue, token_create(TOKEN_LOGIC_OPE, create_token_value("&&"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo2", "non"), NULL));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")"), NULL));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value2("echo3", "test"), NULL));

	write_result(&queue, data);
}

static char	*add_element_test(char *str, char *add)
{
	char	*new;
	char	*pre;

	pre = ft_strjoin(str, add);
	free(str);
	new = ft_strjoin(pre, "\n");
	free(pre);
	return (new);
}

void	test_get_tree(char **envp)
{
	size_t	test_number;
	t_data	data;
	char	*str;

	data.env = strdup_tab(envp);

	start_test("parser");
	test_number = 1;

	/*--- test 1 ---*/
	test_get_tree1(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "cat l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 2 ---*/
	test_get_tree2(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "echo l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 3 ---*/
	test_get_tree3(&data);
	assert_equal_err("minishell: syntax error near unexpected token `&&'\n", &test_number);

	/*--- test 4 ---*/
	test_get_tree4(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "grep l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 5 ---*/
	test_get_tree5(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "<redir1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "<redir2");
	str = add_element_test(str, "grep l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 6 ---*/
	test_get_tree6(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "<redir1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "||");
	str = add_element_test(str, "3");
	str = add_element_test(str, "<redir2");
	str = add_element_test(str, "grep l r");
	str = add_element_test(str, "cut l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 7 ---*/
	test_get_tree7(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "2");
	str = add_element_test(str, "<redir1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "3");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "<redir2");
	str = add_element_test(str, "grep l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 8 ---*/
	test_get_tree8(&data);
	assert_equal_err("minishell: syntax error near unexpected token `('\n", &test_number);

	/*--- test 9 ---*/
	test_get_tree9(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "<redir1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "||");
	str = add_element_test(str, "3");
	str = add_element_test(str, "<redir2");
	str = add_element_test(str, "grep l r");
	str = add_element_test(str, "cut l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 10 ---*/
	test_get_tree10(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 11 ---*/
	test_get_tree11(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "echo l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 12 ---*/
	test_get_tree12(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)'\n", &test_number);


	/*--- test 13 ---*/
	test_get_tree13(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)'\n", &test_number);


	/*--- test 14 ---*/
	test_get_tree14(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "|");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "cat l r");
	assert_equal_out(str, &test_number);
	free(str);


	/*--- test 15 ---*/
	test_get_tree15(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "cat l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 16 ---*/
	test_get_tree16(&data);
	assert_equal_out("", &test_number);

	/*--- test 17 ---*/// <redir1 && cat | (<redir2 grep || (<redir3))
	test_get_tree17(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "<redir1 l r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "||");
	str = add_element_test(str, "3");
	str = add_element_test(str, "<redir2");
	str = add_element_test(str, "grep l r");
	str = add_element_test(str, "<redir3 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 18 ---*/
	test_get_tree18(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "<redir1 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 19 ---*/
	test_get_tree19(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "|1");
	str = add_element_test(str, "1");
	str = add_element_test(str, "<redir1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|2");
	str = add_element_test(str, "2");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "|3");
	str = add_element_test(str, "3");
	str = add_element_test(str, "<redir2");
	str = add_element_test(str, "grep l r");
	str = add_element_test(str, "cut l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 20 ---*/
	test_get_tree20(&data);
	assert_equal_err("minishell: syntax error near unexpected token `|'\n", &test_number);

	/*--- test 21 ---*/
	test_get_tree21(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 22 ---*/
	test_get_tree22(&data);
	assert_equal_err("minishell: syntax error near unexpected token `('\n", &test_number);

	/*--- test 23 ---*/
	test_get_tree23(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 24 ---*/
	test_get_tree24(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)1'\n", &test_number);

	/*--- test 25 ---*/
	test_get_tree25(&data);
	assert_equal_err("minishell: syntax error near unexpected token `grep'\n", &test_number);

	/*--- test 26 ---*/
	test_get_tree26(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 27 ---*/
	test_get_tree27(&data);
	assert_equal_err("minishell: syntax error near unexpected token `&&'\n", &test_number);

	/*--- test 28 ---*/
	test_get_tree28(&data);
	assert_equal_err("minishell: syntax error near unexpected token `('\n", &test_number);

	/*--- test 29 ---*/
	test_get_tree29(&data);
	assert_equal_err("minishell: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 30 ---*/
	test_get_tree30(&data);
	assert_equal_err("minishell: syntax error near unexpected token `('\n", &test_number);

	/*--- test 31 ---*/
	test_get_tree31(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 32 ---*/
	test_get_tree32(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 33 ---*/
	test_get_tree33(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 34 ---*/
	test_get_tree34(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 35 ---*/
	test_get_tree35(&data);
	assert_equal_err("minishell: syntax error near unexpected token `&&'\n", &test_number);

	/*--- test 36 ---*/
	test_get_tree36(&data);
	assert_equal_err("minishell: syntax error near unexpected token `&&'\n", &test_number);

	/*--- test 37 ---*/
	test_get_tree37(&data);
	assert_equal_err("minishell: syntax error near unexpected token `>'\n", &test_number);

	/*--- test 38 ---*/
	test_get_tree38(&data);
	assert_equal_err("minishell: syntax error near unexpected token `>>'\n", &test_number);

	/*--- test 39 ---*/
	test_get_tree39(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "|1");
	str = add_element_test(str, "|3");
	str = add_element_test(str, "2");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|2");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "wc l r");
	str = add_element_test(str, "3");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "sort l r");
	str = add_element_test(str, "4");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "grep l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 40 ---*/
	test_get_tree40(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "|1");
	str = add_element_test(str, "|3");
	str = add_element_test(str, "2");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|2");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "wc l r");
	str = add_element_test(str, "3");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "sort l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 41 ---*/
	test_get_tree41(&data);
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "|1");
	str = add_element_test(str, "|3");
	str = add_element_test(str, "2");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "|2");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "wc l r");
	str = add_element_test(str, "3");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "sort l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 42 ---*/
	test_get_tree42(&data);
	assert_equal_err("minishell: syntax error near unexpected token `('\n", &test_number);

	/*--- test 43 ---*/
	test_get_tree43(&data);
	assert_equal_err("minishell: syntax error near unexpected token `('\n", &test_number);

	/*--- test 44 ---*/
	test_get_tree44(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 45 ---*/
	test_get_tree45(&data);
	assert_equal_err("minishell: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 46 ---*/
	test_get_tree46(&data);
	assert_equal_err("minishell: syntax error near unexpected token `echo3'\n", &test_number);

	ft_clean_matrix((void **)data.env);
}
