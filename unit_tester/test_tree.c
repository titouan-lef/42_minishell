/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:51:26 by tle-floc          #+#    #+#             */
/*   Updated: 2025/01/04 16:19:08 by tle-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

static void test_tree_is_empty(void)
{
    size_t test_number;

	start_test("tree_is_empty");
	test_number = 1;
}

static void test_tree_add_parent(void)
{
    size_t test_number;

	start_test("tree_add_parent");
	test_number = 1;
}

static void test_tree_clear(void)
{
    size_t test_number;

	start_test("tree_clear");
	test_number = 1;
}

static void test_tree_create(void)
{
    size_t test_number;

	start_test("tree_create");
	test_number = 1;
}

static void test_tree_push_left(void)
{
    size_t test_number;

	start_test("tree_push_left");
	test_number = 1;
}

static void test_tree_push_right(void)
{
    size_t test_number;

	start_test("tree_push_right");
	test_number = 1;
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