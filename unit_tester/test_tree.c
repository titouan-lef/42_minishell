/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:51:26 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/28 17:40:56 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static void	test_tree_is_empty(void)
{
	size_t	test_number;
	start_test("tree_is_empty");
	test_number = 1;

	t_tree	*tree = NULL;
	assert_true(tree_is_empty(tree), &test_number);

	t_token	token = token_create(TOKEN_PIPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	tree = tree_create(token);
	assert_false(tree_is_empty(tree), &test_number);

	tree_clear(&tree);
}

static void	test_tree_add_parent(void)
{
	size_t	test_number;
	start_test("tree_add_parent");
	test_number = 1;

	t_tree	*tree = NULL;
	t_token	token1 = token_create(TOKEN_CMD, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	token2 = token_create(TOKEN_PIPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	tree = tree_add_parent(tree, token1);
	assert_equal_i(TOKEN_CMD, tree->token.name, &test_number);
	assert_null(tree->left, &test_number);
	assert_null(tree->right, &test_number);
	tree = tree_add_parent(tree, token2);
	assert_equal_i(TOKEN_PIPE, tree->token.name, &test_number);
	assert_not_null(tree->left, &test_number);
	assert_null(tree->right, &test_number);
	assert_equal_i(TOKEN_CMD, tree->left->token.name, &test_number);
	assert_null(tree->left->left, &test_number);
	assert_null(tree->left->right, &test_number);

	tree_clear(&tree);
}

static void	test_tree_clear(void)
{
	size_t	test_number;
	start_test("tree_clear");
	test_number = 1;

	t_token	token1 = token_create(TOKEN_CMD, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	token2 = token_create(TOKEN_LOGIC_OPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	token3 = token_create(TOKEN_REDIR, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	token4 = token_create(TOKEN_CMD, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	token5 = token_create(TOKEN_PIPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	token6 = token_create(TOKEN_LOGIC_OPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_tree	*tree1 = tree_create(token1);
	t_tree	*tree2 = tree_create(token2);
	t_tree	*tree3 = tree_create(token3);
	t_tree	*tree4 = tree_create(token4);
	t_tree	*tree5 = tree_create(token5);
	t_tree	*tree6 = tree_create(token6);
	tree1->left = tree2;
	tree2->left = tree3;
	tree2->right = tree4;
	tree4->left = tree5;
	tree4->right = tree6;
	assert_not_null(tree4, &test_number);
	assert_not_null(tree5, &test_number);
	assert_not_null(tree6, &test_number);
	tree_clear(&tree2->right);
	assert_null(tree2->right, &test_number);

	assert_not_null(tree1, &test_number);
	assert_not_null(tree2, &test_number);
	assert_not_null(tree3, &test_number);
	tree_clear(&tree1);
	assert_null(tree1, &test_number);
}

static void	test_tree_create(void)
{
	size_t	test_number;
	start_test("tree_create");
	test_number = 1;

	t_token	token = token_create(TOKEN_CMD, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_tree	*tree = tree_create(token);
	assert_equal_i(TOKEN_CMD, tree->token.name, &test_number);
	assert_null(tree->left, &test_number);
	assert_null(tree->right, &test_number);

	tree_clear(&tree);
}

static void	test_tree_push_left(void)
{
	size_t	test_number;
	start_test("tree_push_left");
	test_number = 1;

	t_tree	*sub_tree;
	t_token	sub_token1 = token_create(TOKEN_CMD, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	sub_token2 = token_create(TOKEN_PIPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	sub_tree = tree_create(sub_token1);
	sub_tree = tree_add_parent(sub_tree, sub_token2);
	t_tree	*tree = NULL;
	t_tree	*aux;
	t_token token = token_create(TOKEN_REDIR, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_out	outputs;

	redirect_outputs(&outputs);
	tree_push_left(tree, sub_tree);
	set_normal_outputs(&outputs);
	assert_equal_err("Error tree push left\n", &test_number);

	tree = tree_create(token);
	tree->left = sub_tree;
	redirect_outputs(&outputs);
	tree_push_left(tree, sub_tree);
	set_normal_outputs(&outputs);
	assert_equal_err("Error tree push left\n", &test_number);

	tree->left = NULL;
	redirect_outputs(&outputs);
	tree_push_left(tree, sub_tree);
	set_normal_outputs(&outputs);
	assert_equal_err("", &test_number);
	assert_equal_i(TOKEN_REDIR, tree->token.name, &test_number);
	assert_not_null(tree->left, &test_number);
	assert_null(tree->right, &test_number);
	aux = tree->left;
	assert_equal_i(TOKEN_PIPE, aux->token.name, &test_number);
	assert_not_null(aux->left, &test_number);
	assert_null(aux->right, &test_number);
	aux = aux->left;
	assert_equal_i(TOKEN_CMD, aux->token.name, &test_number);
	assert_null(aux->left, &test_number);
	assert_null(aux->right, &test_number);

	tree_clear(&tree);
}

static void	test_tree_push_right(void)
{
	size_t	test_number;
	start_test("tree_push_right");
	test_number = 1;

	t_tree	*sub_tree;
	t_token	sub_token1 = token_create(TOKEN_CMD, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_token	sub_token2 = token_create(TOKEN_PIPE, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	sub_tree = tree_create(sub_token1);
	sub_tree = tree_add_parent(sub_tree, sub_token2);
	t_tree	*tree = NULL;
	t_tree	*aux;
	t_token	token = token_create(TOKEN_REDIR, calloc(1, sizeof(char *)), calloc(1, sizeof(char *)));
	t_out	outputs;

	redirect_outputs(&outputs);
	tree_push_right(tree, sub_tree);
	set_normal_outputs(&outputs);
	assert_equal_err("Error tree push right\n", &test_number);

	tree = tree_create(token);
	tree->right = sub_tree;
	redirect_outputs(&outputs);
	tree_push_right(tree, sub_tree);
	set_normal_outputs(&outputs);
	assert_equal_err("Error tree push right\n", &test_number);

	tree->right = NULL;
	redirect_outputs(&outputs);
	tree_push_right(tree, sub_tree);
	set_normal_outputs(&outputs);
	assert_equal_err("", &test_number);
	assert_equal_i(TOKEN_REDIR, tree->token.name, &test_number);
	assert_null(tree->left, &test_number);
	assert_not_null(tree->right, &test_number);
	aux = tree->right;
	assert_equal_i(TOKEN_PIPE, aux->token.name, &test_number);
	assert_not_null(aux->left, &test_number);
	assert_null(aux->right, &test_number);
	aux = aux->left;
	assert_equal_i(TOKEN_CMD, aux->token.name, &test_number);
	assert_null(aux->left, &test_number);
	assert_null(aux->right, &test_number);

	tree_clear(&tree);
}

void	test_tree(void)
{
	test_tree_is_empty();
	test_tree_add_parent();
	test_tree_clear();
	test_tree_create();
	test_tree_push_left();
	test_tree_push_right();
}