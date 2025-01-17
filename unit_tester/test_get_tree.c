/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:12:14 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/17 17:36:49 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

typedef struct s_node
{
	t_tree 			*tree;
	int				depth;
	struct s_node	*next;
}	t_node;

typedef struct s_queue_node
{
	t_node	*head;
	t_node	*tail;
}	t_queue_node;

/*static void	tree_traversal_in_order(t_tree *tree)
{
	if (tree != NULL)
	{
		tree_traversal_in_order(tree->left);
		ft_printf("node : %d, value : %s\n", tree->tree.name, tree->tree.value[0]);
		tree_traversal_in_order(tree->right);
	}
}*/

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

static void write_result(t_queue *queue)
{
	t_out	outputs;
	t_data	data;
	t_tree *tree;

	redirect_outputs(&outputs);
	data = get_tree_data(queue);
	tree = data.tree;
	clear_here_docs(data.lst);
	breadth_first_search(tree);
	set_normal_outputs(&outputs);
	tree_clear(&tree);
}

// echo && cat
static void test_get_tree1(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));

	write_result(&queue);
}

// echo
static void test_get_tree2(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));

	write_result(&queue);
}

// echo &&
static void test_get_tree3(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));

	write_result(&queue);
}

// echo && cat | grep
static void test_get_tree4(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));

	write_result(&queue);
}

// <redir1 echo && cat | <redir2 grep || cut
static void test_get_tree5(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));

	write_result(&queue);
}

// <redir1 echo && cat | (<redir2 grep || cut)
static void test_get_tree6(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// <redir1 echo && cat | <redir2 grep || cut
static void test_get_tree7(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut")));

	write_result(&queue);
}

// <redir1 echo && cat | (<redir2 grep (|| cut))
static void test_get_tree8(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// <redir1 echo && cat | (<redir2 grep || (cut))
static void test_get_tree9(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// ()
static void test_get_tree10(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// (echo)
static void test_get_tree11(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// (echo ||)
static void test_get_tree12(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// (echo |)
static void test_get_tree13(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// (echo | cat)
static void test_get_tree14(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// (echo || cat)
static void test_get_tree15(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

//
static void test_get_tree16(void)
{
	t_queue	queue = queue_create();

	write_result(&queue);
}

// <redir1 && cat | (<redir2 grep || (<redir3))
static void test_get_tree17(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("||")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir3")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// <redir1
static void test_get_tree18(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));

	write_result(&queue);
}

// <redir1 echo | cat | <redir2 grep | cut
static void test_get_tree19(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|2")));
	queue_push(&queue, token_create(TOKEN_REDIR, create_token_value("<redir2")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|3")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cut")));

	write_result(&queue);
}

// echo |
static void test_get_tree20(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));

	write_result(&queue);
}

// echo | )
static void test_get_tree21(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// echo | (
static void test_get_tree22(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));

	write_result(&queue);
}

// echo | (cat && grep))
static void test_get_tree23(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// echo | )cat && grep()
static void test_get_tree24(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")1")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// echo | cat (grep)
static void test_get_tree25(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PIPE, create_token_value("|")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("grep")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// echo (
static void test_get_tree26(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));

	write_result(&queue);
}

// &&
static void test_get_tree27(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_OPE, create_token_value("&&")));

	write_result(&queue);
}

// echo (( cat )
static void test_get_tree28(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("echo")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));
	queue_push(&queue, token_create(TOKEN_CMD, create_token_value("cat")));
	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// )
static void test_get_tree29(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_CLOSE, create_token_value(")")));

	write_result(&queue);
}

// (
static void test_get_tree30(void)
{
	t_queue	queue = queue_create();

	queue_push(&queue, token_create(TOKEN_PAR_OPEN, create_token_value("(")));

	write_result(&queue);
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

void	test_get_tree(void)
{
	size_t	test_number;
	char	*str;

	start_test("get_tree_data");
	test_number = 1;

	/*--- test 1 ---*/
	test_get_tree1();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "cat l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 2 ---*/
	test_get_tree2();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "echo l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 3 ---*/
	test_get_tree3();
	assert_equal_err("bash: syntax error near unexpected token `&&'\n", &test_number);

	/*--- test 4 ---*/
	test_get_tree4();
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
	test_get_tree5();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "<redir1 l r");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "grep r");
	str = add_element_test(str, "3");
	str = add_element_test(str, "<redir2 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 6 ---*/
	test_get_tree6();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "<redir1 l r");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "||");
	str = add_element_test(str, "3");
	str = add_element_test(str, "grep r");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "4");
	str = add_element_test(str, "<redir2 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 7 ---*/
	test_get_tree7();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "2");
	str = add_element_test(str, "echo r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "3");
	str = add_element_test(str, "<redir1 l r");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "grep r");
	str = add_element_test(str, "4");
	str = add_element_test(str, "<redir2 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 8 ---*/
	test_get_tree8();
	assert_equal_err("bash: syntax error near unexpected token `||'\n", &test_number);

	/*--- test 9 ---*/
	test_get_tree9();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "&&");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo r");
	str = add_element_test(str, "|");
	str = add_element_test(str, "2");
	str = add_element_test(str, "<redir1 l r");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "||");
	str = add_element_test(str, "3");
	str = add_element_test(str, "grep r");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "4");
	str = add_element_test(str, "<redir2 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 10 ---*/
	test_get_tree10();
	assert_equal_err("bash: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 11 ---*/
	test_get_tree11();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "echo l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 12 ---*/
	test_get_tree12();
	assert_equal_err("bash: syntax error near unexpected token `)'\n", &test_number);


	/*--- test 13 ---*/
	test_get_tree13();
	assert_equal_err("bash: syntax error near unexpected token `)'\n", &test_number);


	/*--- test 14 ---*/
	test_get_tree14();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "|");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "cat l r");
	assert_equal_out(str, &test_number);
	free(str);


	/*--- test 15 ---*/
	test_get_tree15();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "||");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo l r");
	str = add_element_test(str, "cat l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 16 ---*/
	test_get_tree16();
	assert_equal_out("", &test_number);

	/*--- test 17 ---*/
	test_get_tree17();
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
	str = add_element_test(str, "grep r");
	str = add_element_test(str, "<redir3 l r");
	str = add_element_test(str, "4");
	str = add_element_test(str, "<redir2 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 18 ---*/
	test_get_tree18();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "<redir1 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 19 ---*/
	test_get_tree19();
	str = calloc(1, sizeof(char));
	str = add_element_test(str, "0");
	str = add_element_test(str, "|1");
	str = add_element_test(str, "1");
	str = add_element_test(str, "echo r");
	str = add_element_test(str, "|2");
	str = add_element_test(str, "2");
	str = add_element_test(str, "<redir1 l r");
	str = add_element_test(str, "cat l r");
	str = add_element_test(str, "|3");
	str = add_element_test(str, "3");
	str = add_element_test(str, "grep r");
	str = add_element_test(str, "cut l r");
	str = add_element_test(str, "4");
	str = add_element_test(str, "<redir2 l r");
	assert_equal_out(str, &test_number);
	free(str);

	/*--- test 20 ---*/
	test_get_tree20();
	assert_equal_err("bash: syntax error near unexpected token `|'\n", &test_number);

	/*--- test 21 ---*/
	test_get_tree21();
	assert_equal_err("bash: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 22 ---*/
	test_get_tree22();
	assert_equal_err("bash: syntax error near unexpected token `('\n", &test_number);

	/*--- test 23 ---*/
	test_get_tree23();
	assert_equal_err("bash: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 24 ---*/
	test_get_tree24();
	assert_equal_err("bash: syntax error near unexpected token `)1'\n", &test_number);

	/*--- test 25 ---*/
	test_get_tree25();
	assert_equal_err("bash: syntax error near unexpected token `grep'\n", &test_number);

	/*--- test 26 ---*/
	test_get_tree26();
	assert_equal_err("bash: syntax error near unexpected token `newline'\n", &test_number);

	/*--- test 27 ---*/
	test_get_tree27();
	assert_equal_err("bash: syntax error near unexpected token `&&'\n", &test_number);

	/*--- test 28 ---*/
	test_get_tree28();
	assert_equal_err("bash: syntax error near unexpected token `('\n", &test_number);

	/*--- test 29 ---*/
	test_get_tree29();
	assert_equal_err("bash: syntax error near unexpected token `)'\n", &test_number);

	/*--- test 30 ---*/
	test_get_tree30();
	assert_equal_err("bash: syntax error near unexpected token `('\n", &test_number);
}
