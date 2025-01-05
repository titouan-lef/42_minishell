/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:51:26 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/05 14:25:33 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static void test_tree_is_empty(void)
{
    size_t  test_number;
	start_test("tree_is_empty");
	test_number = 1;

    /*t_tree  *tree;
    tree = NULL;
    assert_true(tree_is_empty(tree), &test_number);

    t_token token;
    tree = tree_create(token);
    assert_false(tree_is_empty(tree), &test_number);

    tree_clear(&tree);*/
}

static void test_tree_add_parent(void)
{
    size_t  test_number;
	start_test("tree_add_parent");
	test_number = 1;

    /*t_tree  *tree;
    t_token token1;
    t_token token2;
    tree_add_parent(&tree, token1);
    // check token value
    assert_null(tree->left, &test_number);
    assert_null(tree->right, &test_number);
    tree_add_parent(&tree, token2);
    // check token value
    assert_not_null(tree->left, &test_number);
    assert_null(tree->right, &test_number);

    // check next token value
    assert_null(tree->left->left, &test_number);
    assert_null(tree->left->right, &test_number);

    tree_clear(&tree);*/
}

static void test_tree_clear(void)
{
    size_t  test_number;
	start_test("tree_clear");
	test_number = 1;

    /*t_tree  *tree1;
    t_tree  *tree2;
    t_tree  *tree3;
    t_tree  *tree4;
    t_tree  *tree5;
    t_token token1;
    t_token token2;
    t_token token3;
    t_token token4;
    t_token token5;
    tree1 = tree_create(token1);
    tree2 = tree_create(token2);
    tree3 = tree_create(token3);
    tree4 = tree_create(token4);
    tree5 = tree_create(token5);
    tree1->left = tree2;
    tree2->left = tree3;
    tree2->right = tree4;
    tree4->left = tree5;
    assert_not_null(tree1, &test_number);
    assert_not_null(tree2, &test_number);
    assert_not_null(tree3, &test_number);
    assert_not_null(tree4, &test_number);
    assert_not_null(tree5, &test_number);
    tree_clear(&tree1);
    assert_null(tree1, &test_number);
    assert_null(tree2, &test_number);
    assert_null(tree3, &test_number);
    assert_null(tree4, &test_number);
    assert_null(tree5, &test_number);*/
}

static void test_tree_create(void)
{
    size_t  test_number;
	start_test("tree_create");
	test_number = 1;

    /*t_tree  *tree;
    t_token token;
    tree = tree_create(token);
    // check token value
    assert_null(tree->left, &test_number);
    assert_null(tree->right, &test_number);*/
}

static void test_tree_push_left(void)
{
    size_t  test_number;
	start_test("tree_push_left");
	test_number = 1;

    /*t_tree  *sub_tree;
    t_token sub_token1;
    t_token sub_token2;
    sub_tree = tree_create(sub_token1);
    tree_add_parent(&sub_tree, sub_token2);
    t_tree  *tree;
    t_tree  *aux;
    t_token token;
    tree = NULL;
    tree_push_left(tree, sub_tree);
    // check message error
    tree = tree_create(token);
    tree->left = sub_tree;
    tree_push_left(tree, sub_tree);
    // check message error
    tree->left = NULL;
    tree_push_left(tree, sub_tree);
    // check token
    assert_not_null(tree->left, &test_number);
    assert_null(tree->right, &test_number);
    aux = tree->left;
    // check sub_token2
    assert_not_null(aux->left, &test_number);
    assert_null(aux->right, &test_number);
    aux = aux->left;
    // check sub_token1
    assert_null(aux->left, &test_number);
    assert_null(aux->right, &test_number);

    tree_clear(&tree);*/
}

static void test_tree_push_right(void)
{
    size_t  test_number;
	start_test("tree_push_right");
	test_number = 1;

    /*t_tree  *sub_tree;
    t_token sub_token1;
    t_token sub_token2;
    sub_tree = tree_create(sub_token1);
    tree_add_parent(&sub_tree, sub_token2);
    t_tree  *tree;
    t_tree  *aux;
    t_token token;
    tree = NULL;
    tree_push_right(tree, sub_tree);
    // check message error
    tree = tree_create(token);
    tree->right = sub_tree;
    tree_push_right(tree, sub_tree);
    // check message error
    tree->right = NULL;
    tree_push_right(tree, sub_tree);
    // check token
    assert_null(tree->left, &test_number);
    assert_not_null(tree->right, &test_number);
    aux = tree->right;
    // check sub_token2
    assert_not_null(aux->left, &test_number);
    assert_null(aux->right, &test_number);
    aux = aux->left;
    // check sub_token1
    assert_null(aux->left, &test_number);
    assert_null(aux->right, &test_number);

    tree_clear(&tree);*/
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